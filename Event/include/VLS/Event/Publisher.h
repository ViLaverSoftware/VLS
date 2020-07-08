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
/// The publisher provide functionality to connect with subscribers. Both will break the 
/// connection by unsubscribing when destructed.
/// Implementation of this abstract class must implement a Subscribe() function that
/// registrates the subscription with a pointer reference to an new Subscriber class.
/// New subscriber classes can be created with :
/// SubscriptionHandler::Unsubscriber::Create(...)
/// It must also implement the pure virtual function SubscriptionHandler::Unsubscribe(...)
/// it will receive a pointer to the Unsubscriber class that was return by the Subscribe
/// class.It must then unsubscribe the subscription.
/// </summary>
class Publisher {

public:

    /// <summary>
    /// 
    /// </summary>
    Publisher(const Publisher&) = delete;
    Publisher() = default;

    /// <summary>
    /// 
    /// </summary>
    /// <param name="">  </param>
    /// <returns>  </returns>
    virtual ~Publisher();

protected:
    /// <summary>
    /// 
    /// </summary>
    /// <param name="">  </param>
    /// <returns>  </returns>
    bool Subscribe(Subscriber& subscriber);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="">  </param>
    virtual void OnUnsubscribe(Subscriber *subscriber) = 0;

private:
    /// <summary>
    /// 
    /// </summary>
    /// <param name="">  </param>
    /// <returns>  </returns>
    bool _unsubscribe(Subscriber* subscriber, bool notify = true);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="">  </param>
    /// <returns>  </returns>
    void _upsubscribeAll(bool notify = true);


private:
    /// <summary>
    /// 
    /// </summary>
    std::vector<Subscriber*> m_subscribers;

    friend class Subscriber;
};

}
