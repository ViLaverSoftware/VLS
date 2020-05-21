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
#include "VLS/Event/Subscriber.h"

#include "VLS/Event/Publisher.h"

#include <assert.h>

namespace VLS::Event {

Subscriber::~Subscriber()
{
    UnsubscribeAll();
}

void Subscriber::UnsubscribeAll()
{
    while (!m_publishers.empty()) {
        m_publishers.back()->_unsubscribe(this);
    }
}

bool Subscriber::Unsubscribe(Publisher& publisher)
{
    return publisher._unsubscribe(this);
}

size_t Subscriber::PublisherCount() const
{
    return m_publishers.size();
}

bool Subscriber::_subscribe(Publisher* publisher)
{
    auto it = std::find(m_publishers.begin(), m_publishers.end(), publisher);
    if (it != m_publishers.end()) { return false; }
    m_publishers.push_back(publisher);
    return true;
}

bool Subscriber::_unsubsribe(Publisher* publisher)
{
    auto it = std::find(m_publishers.begin(), m_publishers.end(), publisher);
    if (it == m_publishers.end()) { return false; }
    m_publishers.erase(it);
    return true;
}

}