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

#include <memory>
#include <vector>

namespace VLS::Event {

class Publisher;

/// <summary>
/// Can subscribe to a publisher derived object.
/// </summary>
/// <remarks>
/// One subscriber can subscribe to multiple publishers and will automatically
/// unsubscribe when deallocated.
/// </remarks>
class Subscriber {
 public:
  using UPtr = std::unique_ptr<Subscriber>;

  /// <summary>
  /// Copy the object is not allowed.
  /// </summary>
  /// <remarks>
  /// Copy would break the subscriber functionality.
  /// </remarks>
  Subscriber(const Subscriber&) = delete;
  Subscriber() = default;

  /// <remarks>
  /// Automatically unsubscribes from all existing subscriptions.
  /// </remarks>
  virtual ~Subscriber();

  /// <summary>
  /// Unsubscribes from all subscriptions.
  /// </summary>
  void UnsubscribeAll();

  /// <summary>
  /// Unsubscribes from subscriptions to the publisher.
  /// </summary>
  /// <param name="publisher"> Publisher object that is unsubscribed from.
  /// </param> <returns> True is subscription was successful. </returns>
  bool Unsubscribe(Publisher& publisher);

  /// <summary>
  /// Returns the number of publishers with an active subscription.
  /// </summary>
  /// <returns> Number of publishers with an active subscription. </returns>
  size_t PublisherCount() const;

 private:
  /// <summary>
  /// Subscribes to a publisher.
  /// </summary>
  /// <remarks>
  /// Used by the publisher to register when a subscriptions has been made.
  /// </remarks>
  /// <param name="publisher"> Publisher object pointer. </param>
  /// <returns> True if publisher has been added. </returns>
  bool _subscribe(Publisher* publisher);

  /// <summary>
  /// Unsubscribes a publisher.
  /// </summary>
  /// <remarks>
  /// Used by the publisher to remove registration after the subscriber as been
  /// unsubscribed.
  /// </remarks>
  /// <param name=""> Publisher object pointer. </param>
  /// <returns> True if the publisher has been removed. </returns>
  bool _unsubsribe(Publisher* publisher);

 private:
  /// <summary>
  /// List of active publishers.
  /// </summary>
  std::vector<Publisher*> m_publishers;

  friend class Publisher;
};

}  // namespace VLS::Event
