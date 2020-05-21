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
#pragma warning(push, 0)
#include "gtest/gtest.h"
#pragma warning(pop)

#include "VLS/Event/Publisher.h"
#include "VLS/Event/Subscriber.h"

#include <string>
#include <memory>
#include <map>
#include <io.h>

class Event {
public:
    Event(const std::string& name) : m_name(name) {}
    const std::string& name() const { return m_name; }
private:
    std::string m_name;
};

class EventPublisher : public VLS::Event::Publisher
{
public:

    std::shared_ptr<VLS::Event::Subscriber> Subscribe(const Event* event) {
        //std::cout << "Subscribe: " << event->name().c_str();
        auto subPtr = std::make_shared<VLS::Event::Subscriber>();
        VLS::Event::Publisher::Subscribe(*subPtr.get());
        m_eventMap[subPtr.get()] = event;
        return subPtr;
    }

    size_t Count() const {
        return m_eventMap.size();
    }

protected:
    void OnUnsubscribe(VLS::Event::Subscriber* subscriber) override
    {
        const Event* event = m_eventMap[subscriber];
        //std::cout << "Unsubscribe: " << event->name().c_str();
        m_eventMap.erase(subscriber);
    }
private:
    std::map<VLS::Event::Subscriber*, const Event*> m_eventMap;
};

TEST(VLSEventPubSub, UnsubscribeAll) {
    EventPublisher ePub;
    Event e("Ted");
    EXPECT_EQ(ePub.Count(), 0);
    auto sub = ePub.Subscribe(&e);
    EXPECT_EQ(ePub.Count(), 1);
    sub->UnsubscribeAll();
    EXPECT_EQ(ePub.Count(), 0);
}

TEST(VLSEventPubSub, Destructor) {
    EventPublisher ePub;
    Event e("Ted");
    EXPECT_EQ(ePub.Count(), 0);
    auto sub = ePub.Subscribe(&e);
    EXPECT_EQ(ePub.Count(), 1);
    sub.reset();
    EXPECT_EQ(ePub.Count(), 0);
}