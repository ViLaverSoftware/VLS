/*
 * Copyright 2020 Vilaversoftware IVS (http://vilaversoftware.dk/)
 * Author: Mikkel Nøhr Løvgreen (ml@vilaversoftware.dk)
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

#include "VLS/Event/Publisher.h"
#include "VLS/Event/Subscriber.h"
#include "VLS/Event/IEventLoop.h"

#include <chrono>

namespace VLS::Event {

/// <summary>
/// 
/// </summary>
template<typename ... Types>
class IEventHandler {
public:
    /// <summary> 
    /// Subscribes to triggered events.
    /// The lambda function argument will be called when the event is triggered. The arguments 
    /// used to trigger the event will be passed on to the lambda function.
    /// An unique pointer to a subcriber is return. The subscriber can be used to unsubscribe 
    /// to events, and it will automaticly unsubscribe when the subscriber is descructed. 
    /// </summary>
    /// <param name="func"> Lambda function that take the event arguments. </param>
    /// <param name="eventLoop">  </param>
    /// <returns> </returns>
    virtual Subscriber::UPtr Subscribe(const std::function<void(Types ...)>& func, IEventLoop* eventLoop = nullptr) = 0;

    /// <summary>
    /// </summary>
    /// <param name="func"> Free function that take the event arguments. </param>
    /// <param name="eventLoop">  </param>
    /// <returns> </returns>
    virtual Subscriber::UPtr Subscribe(void(*func)(Types ...), IEventLoop* eventLoop = nullptr) = 0;

    /// <summary>
    /// </summary>
    /// <param name="subscriber">  </param>
    /// <param name="func"> Lambda function that take the event arguments. </param>
    /// <param name="eventLoop">  </param>
    virtual bool Subscribe(Subscriber& subscriber, const std::function<void(Types ...)>& func, IEventLoop *eventLoop = nullptr) = 0;

    /// <summary>
    /// </summary>
    /// <param name="subscriber">  </param>
    /// <param name="func"> Free function that take the event arguments. </param>
    /// <param name="eventLoop">  </param>
    virtual bool Subscribe(Subscriber& subscriber, void(*func)(Types ...), IEventLoop* eventLoop = nullptr) = 0;

    /// <summary>
    /// </summary>
    /// <param name="func"> Lambda function that take the event arguments. </param>
    /// <param name="eventLoop">  </param>
    virtual void SubscribePersistent(const std::function<void(Types ...)>& func, IEventLoop* eventLoop = nullptr) = 0;

    /// <summary>
    /// </summary>
    /// <param name="func"> Free function that take the event arguments. </param>
    /// <param name="eventLoop">  </param>
    virtual void SubscribePersistent(void(*func)(Types ...), IEventLoop* eventLoop = nullptr) = 0;

    /// <summary>
    /// </summary>
    /// <param name="timeout">  </param>
    /// <returns> </returns>
    virtual std::shared_ptr<std::tuple<Types ...>> Wait(std::chrono::milliseconds timeout = std::chrono::minutes(1)) = 0;
};

}