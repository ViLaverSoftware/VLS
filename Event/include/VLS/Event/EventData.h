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

#include <VLS/Event/IEventLoop.h>
#include <VLS/Event/Subscriber.h>

namespace VLS::Event {

/// <summary>
/// This data structure is used internally in the EventHandler to store data
/// related to a single event subscription.
/// </summary>
/// <remarks>
/// 1. Optional Subscriber used to unsubscribe to the event.
/// 2. Callable function with the arguments of the variadic template.
/// 3. Optional event loop. If specified the event will be Enqueued to the event
/// loop when triggered.
/// </remarks>
template <typename... Types>
struct EventData {
  /// <summary>
  ///
  /// </summary>
  EventData(Subscriber* s, std::function<void(Types...)> f, IEventLoop* e)
      : subscriber(s), func(f), eventLoop(e) {}

  /// <summary>
  /// The subscriber can unsubscribe from the event and will automatically do so
  /// if it is deallocated.
  /// </summary>
  /// <remarks>
  /// The subscriber is optional.
  /// If no set the subscription to the event is persistent.
  /// </remarks>
  Subscriber* subscriber;

  /// <summary>
  /// The function will be called when the event is triggered.
  /// </summary>
  /// <remarks>
  /// The arguments used to call the function is the arguments used to trigger
  /// the event.
  /// </remarks>
  std::function<void(Types...)> func;

  /// <summary>
  /// The callable function will be packed in a callable void(void) function if
  /// necessary and enqueued on the event loop when the event is triggered.
  /// </summary>
  /// <remarks>
  /// The event loop is optional.
  /// If not set the callable function will be called directly on the same
  /// thread as the event is triggered.
  /// </remarks>
  IEventLoop* eventLoop;
};

}  // namespace VLS::Event
