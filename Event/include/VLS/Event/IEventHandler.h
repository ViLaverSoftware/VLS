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

#include <VLS/Event/Bind.h>
#include <VLS/Event/IEventLoop.h>
#include <VLS/Event/Publisher.h>
#include <VLS/Event/Subscriber.h>

namespace VLS::Event {

/// <summary>
/// Interface class that contains the functions that can be used to subscribe to
/// EventHandler events.
/// </summary>
/// <remarks>
/// The interface makes it possible to expose subscriptions functions without
/// exposing the trigger function. It also make it possible for classes that has
/// events to have interfaces without needed to implement the event in the
/// interface. Having an interface for the EventHandler also makes it easy to
/// mock it.
/// </remarks>
template <typename... Types>
class IEventHandler {
 public:
  /// <summary>
  /// Subscribes to the event by providing a callable that will be called when
  /// the event is triggered.
  /// </summary>
  /// <remarks>
  /// The callable will be enqueued to the event loop when the event is
  /// triggered if an event loop is provided. The returned subscriber object can
  /// unsubscribe and will automatically unsubscribe if deconstructed. Warning:
  /// If the returned subscriber is not received unsubscribe will be triggered
  /// immediately after the subscription.
  /// </remarks>
  /// <param name="func"> Callable that will be called when the event is
  /// triggered. </param> <param name="eventLoop"> Optional thread where the
  /// callable will be called if provided. </param> <returns> Unique pointer to
  /// subscribe object with a subscription to this event. </returns>
  virtual Subscriber::UPtr Subscribe(const std::function<void(Types...)>& func,
                                     IEventLoop* eventLoop = nullptr) = 0;

  /// <summary>
  /// Subscribes to the event by providing a callable that will be called when
  /// the event is triggered.
  /// </summary>
  /// <remarks>
  /// The callable will be enqueued to the event loop when the event is
  /// triggered if an event loop is provided. The subscriber will receive a
  /// subscription so it can unsubscribe and will automatically unsubscribe if
  /// deconstructed.
  /// </remarks>
  /// <param name="subscriber"> The subscriber will receive a subscription to
  /// the event so it can unsubscribe to the event. </param> <param name="func">
  /// Callable that will be called when the event is triggered. </param> <param
  /// name="eventLoop"> Optional thread where the callable will be called if
  /// provided. </param>
  virtual bool Subscribe(Subscriber& subscriber,
                         const std::function<void(Types...)>& func,
                         IEventLoop* eventLoop = nullptr) = 0;

  /// <summary>
  /// Subscribes to the event by providing a callable that will be called when
  /// the event is triggered.
  /// </summary>
  /// <remarks>
  /// The callable will be enqueued to the event loop when the event is
  /// triggered if an event loop is provided. It is not possible to unsubscribe
  /// when the persistent version of the subscribe function is used.
  /// </remarks>
  /// <param name="func"> Callable that will be called when the event is
  /// triggered. </param> <param name="eventLoop"> Optional thread where the
  /// callable will be called if provided. </param>
  virtual void SubscribePersistent(const std::function<void(Types...)>& func,
                                   IEventLoop* eventLoop = nullptr) = 0;
};

}  // namespace VLS::Event
