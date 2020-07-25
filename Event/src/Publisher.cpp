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
#include "VLS/Event/Publisher.h"

#include "VLS/Event/Subscriber.h"

#include <assert.h>

namespace VLS::Event {


Publisher::~Publisher()
{
    _upsubscribeAll(false);
}

bool Publisher::Subscribe(Subscriber& subscriber)
{
    auto it = std::find(m_subscribers.begin(), m_subscribers.end(), &subscriber);
    if (it != m_subscribers.end()) { return false; }
    if (subscriber._subscribe(this)) {
        m_subscribers.push_back(&subscriber);
        return true;
    }
    return false;
}

bool Publisher::_unsubscribe(Subscriber *subscriber, bool notify)
{
    assert(subscriber != nullptr);
    auto it = std::find(m_subscribers.begin(), m_subscribers.end(), subscriber);
    if (it == m_subscribers.end()) { return false; }
    m_subscribers.erase(it);

    // Remove the publisher from the subscriber
    bool result = subscriber->_unsubsribe(this);
    assert(result);

    if (notify) {
        OnUnsubscribe(subscriber);
    }

    return result;
}

void Publisher::_upsubscribeAll(bool notify)
{
    while (m_subscribers.size() > 0)
    {
        _unsubscribe(m_subscribers.back(), notify);
    }
}

}
