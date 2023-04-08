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

#include <vector>

namespace VLS::Event {

class Subscriber;

/// <summary>
/// The publisher provide functionality to connect with subscribers.
/// </summary>
/// <remarks>
/// Both subscriber and publisher will break the connection by unsubscribing
/// when destructed. Implementation of this abstract class must implement a
/// Subscribe() function that registrars the subscription with a pointer
/// reference to an new Subscriber class. It must also implement the pure
/// virtual function OnUnsubscribe(Subscriber *subscriber) it will receive a
/// pointer to the subscriber class that unsubscribed.
/// </remarks>
class Publisher {
 public:
  Publisher() = default;

  /// <summary>
  /// Copy constructor is not available because it will break the unsubscribe
  /// functionality
  /// </summary>
  Publisher(const Publisher&) = delete;

  /// <summary>
  /// All references to the object in referenced subscribers will be removed.
  /// </summary>
  virtual ~Publisher();

 protected:
  /// <summary>
  /// Add a reference to the subscriber
  /// </summary>
  /// <remarks>
  /// The reference is used to unsubscribe when the object is deallocated.
  /// Only holds one reference to each subscriber.
  /// </remarks>
  /// <param name="subscriber"> Subscriber object that is subscribing. </param>
  /// <returns> True if new subscriber reference is added. </returns>
  bool Subscribe(Subscriber& subscriber);

  /// <summary>
  /// Pure virtual function called when an subscriber is unsubscribed.
  /// </summary>
  /// <remarks>
  /// It is not triggered when a subscriber is unsubscribed during the
  /// deconstruction of the Publisher.
  /// </remarks>
  /// <param name="subscriber"> Pointer to the subscriber object. </param>
  virtual void OnUnsubscribe(Subscriber* subscriber) = 0;

 private:
  /// <summary>
  /// Removes a subscriber reference.
  /// </summary>
  /// <remarks>
  /// Calls the virtual OnUnsubsribe functions if reference exists and notify is
  /// true.
  /// </remarks>
  /// <param name="subscriber"> Object that will be unsubscribed. </param>
  /// <param name="notify"> OnUnsubscribe will only be called if true. </param>
  /// <returns> True if unsubscribe was successful. </returns>
  bool _unsubscribe(Subscriber* subscriber, bool notify = true);

  /// <summary>
  /// Unsubscribe all referenced objects.
  /// </summary>
  /// <param name="notify"> OnUnsubscribe will only be called if true. </param>
  void _upsubscribeAll(bool notify = true);

 private:
  /// <summary>
  /// List of subscribers with a subscription.
  /// </summary>
  std::vector<Subscriber*> m_subscribers;

  friend class Subscriber;
};

}  // namespace VLS::Event
