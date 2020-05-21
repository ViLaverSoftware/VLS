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

#include "VLS/Event/Subscriber.h"
#include "VLS/Event/IEventHandler.h"

#include <future>

namespace VLS::Event {

/// <summary>
/// This data structure is used internaly in the EventHandler to store data related to a single event subscription.
/// 1. Optional Subscriber used to unsubscribe to the event.
/// 2. Callable function with the arguments of the variadic template.
/// 3. Optional event loop. If specified the event will be Enqueued to the event loop when triggered. 
/// </summary>
template<typename ... Types>
struct EventData {
    /// <summary>
    /// 
    /// </summary>
    EventData(Subscriber* s, std::function<void(Types ...)> f, IEventLoop* e)
        : subscriber(s), func(f), eventLoop(e) {}

    /// <summary>
    /// The subscriber is optional. 
    /// If no set the subscription to the event is persistent.
    /// The subscriber can unsubscribe the event and will automaticly do so if it is dealocated.
    /// </summary>
    Subscriber* subscriber;

    /// <summary>
    /// When the event is triggered the callable func is the function that will be called. 
    /// The arguments used to call the function is the arguments used to trigger the event. 
    /// </summary>
    std::function<void(Types ...)> func;

    /// <summary>
    /// The event loop is optional.
    /// If not set the callable function will be called directly on the same thread as the event is triggered.
    /// The callable function will be packed in a callable void(void) function is nessary and enqueued on the 
    /// event loop when the event is triggered.
    /// </summary>
    IEventLoop* eventLoop;
};

}