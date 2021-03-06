/*
 * Copyright 2020 Vilaversoftware IVS (http://vilaversoftware.dk/)
 * Author: Mikkel N�hr L�vgreen (ml@vilaversoftware.dk)
 * ------------------------------------------------------------------------
 * Licensed to Vilaversoftware IVS who licenses this file to you under the
 * Apache License, Version 2.0 (the "License"); you may not use this file
 * except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <vector>
#include <future>
#include <chrono>
#include <memory>

#include "VLS/Event/Bind.h"
#include "VLS/Event/Publisher.h"
#include "VLS/Event/EventData.h"

// Multiple subscriptions are allowed for each subscriber pr publisher as default but can be changed
// with this flag
//#define VLS_EVENT_ONE_SUBSCRIPTION_PER_SUBSCRIBER

namespace VLS::Event {

/// <summary> 
/// Handles events by providing the possibility to subscribe to and trigger an event, with arguments 
/// matching the variadic temple of the class. 
/// </summary>
/// <remarks>
/// Subscriptions can be persistent(no unsubscribe option) or be handled by a subscriber. 
/// If an reference to a subscriber object is provided it will be used, otherwise a unique 
/// point to a subscriber object will be returned.
/// The subscriber provides functions that can be used to unsubscribe to the event.
/// The subscriber will unsubscribe any existing subscription automatically if deallocated. 
/// 
/// When subscribing to an event, a function needs to be provided with a matching set of 
/// arguments. The function can be a callable std::function<void(...)> (lambda) or a free 
/// function. A member function can also be used, but need to be bound to a callable first.
/// See VLS/Event/Bind.h.
/// 
/// The EventHandler also supports async execution of events. 
/// When subscribing to events an EventLoop can be provided. Instead of calling the supplied 
/// function directly, it will be packed into a void(void) lambda function with all the function 
/// arguments and enqueued on the event loop.
/// 
/// Value, const reference and pointer argument types are supported. Reference arguments are not.
/// Const reference and value arguments types needs a copy constructor. If a class with no copy 
/// constructor needs to be return in an event callback a pointer can be used.
/// 
/// Warning: Proper care should be taking with function argument to make sure they are still 
/// in scope when the event loop gets around to calling the enqueued function. 
/// </remarks>
template<typename ... Types>
class EventHandler : public Publisher, public IEventHandler<Types ...>
{
public:
    explicit EventHandler() = default;

     /// <summary>
     /// Copy constructor is not available because it will break the Unsubscribe functionality
     /// </summary>
    EventHandler(const EventHandler&) = delete;

    /// <summary>
    /// Subscribes to the event by providing a callable that will be called when the event is triggered. 
    /// </summary>
    /// <remarks>
    /// The callable will be enqueued to the event loop when the event is triggered if an event loop is provided.
    /// The returned subscriber object can unsubscribe and will automatically unsubscribe if deconstructed.
    /// Warning: If the returned subscriber is not received unsubscribe will be triggered immediately after
    /// the subscription.
    /// </remarks>
    /// <param name="func"> Callable that will be called when the event is triggered. </param>
    /// <param name="eventLoop"> Optional thread where the callable will be called if provided. </param>
    /// <returns> Unique pointer to subscribe object with a subscription to this event. </returns>
    Subscriber::UPtr Subscribe(const std::function<void(Types ...)>& func, IEventLoop* eventLoop = nullptr) override {
        auto sub = std::make_unique<Subscriber>();
        if (Subscribe(*sub.get(), func, eventLoop)) {
            return std::move(sub);
        }
        return Subscriber::UPtr();
    }

    /// <summary>
    /// Subscribes to the event by providing a callable that will be called when the event is triggered.
    /// </summary>
    /// <remarks>
    /// The callable will be enqueued to the event loop when the event is triggered if an event loop is provided.
    /// The subscriber will receive a subscription so it can unsubscribe and will automatically unsubscribe if deconstructed.
    /// </remarks>
    /// <param name="subscriber"> The subscriber will receive a subscription to the event so it can unsubscribe to the event. </param>
    /// <param name="func"> Callable that will be called when the event is triggered. </param>
    /// <param name="eventLoop"> Optional thread where the callable will be called if provided. </param>
    bool Subscribe(Subscriber& subscriber, const std::function<void(Types ...)>& func, IEventLoop* eventLoop = nullptr) override
    {
        std::lock_guard<std::mutex> guard(m_mutex);
#ifdef VLS_EVENT_ONE_SUBSCRIPTION_PER_SUBSCRIBER
        // Do not subscribe twice
        auto it = std::find_if(m_functionList.begin(), m_functionList.end(),
            [&subscriber](const auto& value) {
                return value->subscriber == &subscriber;
            });
        if (it != m_functionList.end()) { return false; }

        if (Publisher::Subscribe(subscriber)) {
            m_functionList.push_back(std::make_unique<EventData<Types...>>(&subscriber, func, eventLoop));
            return true;
        }
        return false;
#else
        Publisher::Subscribe(subscriber);
        m_functionList.push_back(std::make_unique<EventData<Types...>>(&subscriber, func, eventLoop ));
        return true;
#endif
    }

    /// <summary>
    /// Subscribes to the event by providing a callable that will be called when the event is triggered.
    /// </summary>
    /// <remarks>
    /// The callable will be enqueued to the event loop when the event is triggered if an event loop is provided.
    /// It is not possible to unsubscribe when the persistent version of the subscribe function is used.
    /// </remarks>
    /// <param name="func"> Callable that will be called when the event is triggered. </param>
    /// <param name="eventLoop"> Optional thread where the callable will be called if provided. </param>
    void SubscribePersistent(const std::function<void(Types ...)>& func, IEventLoop* eventLoop = nullptr) override
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        this->m_functionList.push_back(std::make_unique<EventData<Types ...>>(nullptr, func, eventLoop));
    }

    /// <summary>
    /// Triggers the event by calling all the callables subscribed to the event.
    /// </summary>
    /// <remarks>
    /// The event parameters match the template arguments of the class.
    /// </remarks>
    /// <param name="args"> The parameters used to trigger the callables. </param>
    virtual void Trigger(Types ... args)
    {
        // Subscriber data is copied to avoid having the mutex locked when event functions are called.
        // This will prevent a potential deadlocked if subscribers unsubscribe or triggers the same event during event triggered code.
        std::vector<std::pair<std::function<void(Types ...)>, IEventLoop*>> functionList;
        m_mutex.lock();
        for (auto& data : this->m_functionList)
        {
            functionList.emplace_back(data->func, data->eventLoop);
        }
        m_mutex.unlock();

        for (auto data : functionList) {
            if (data.second == nullptr) {
                // triggers the function directly when no eventLopp is defined
                data.first(args ...);
            } else {
                if constexpr (sizeof...(args) == 0) {
                    // The function is already a callable void(void) function so it is just added to the event loop.
                    data.second->Enqueue(data.first);
                } else {
                    // Encapsulates the function call in a void(void) lambda and queue it on the event loop. 
                    data.second->Enqueue(
                        [data, args ...]() {
                            data.first(args ...);
                        }
                    );
                }
            }
        }
    }

protected:
    /// <summary>
    /// Removes the subscriber and related data.
    /// </summary>
    /// <remarks>
    /// This function will be triggered by the publisher base after a subscriber has unsubscribed.
    /// </remarks>
    /// <param name="subscriber"> Subscriber that will be removed. </param>
    void OnUnsubscribe(Subscriber* subscriber) override
    {
        std::lock_guard<std::mutex> guard(m_mutex);

        auto it = std::find_if(m_functionList.begin(), m_functionList.end(), [subscriber](const auto& data) { return data->subscriber == subscriber; });
        while (it != m_functionList.end()) {
            m_functionList.erase(it);
            it = std::find_if(m_functionList.begin(), m_functionList.end(), [subscriber](const auto& data) { return data->subscriber == subscriber; });
        }
    }
    
    /// <summary>
    /// Mutex used to protect the access to the function list.
    /// </summary>
    std::mutex m_mutex;

    /// <summary>
    /// List of subscribed callables.
    /// </summary>
    /// <remarks>
    /// Each item have:
    /// - Required callable with arguments that match the template arguments.
    /// - Optional subscriber that can be used to unsubscribe to the event.
    /// - Optional event loop where the function will be called if provided.
    /// </remarks>
    std::vector<std::unique_ptr<EventData<Types ...>>> m_functionList;
};

} // namespace VLS::Event
