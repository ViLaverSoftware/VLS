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

#include "VLS/Event/EventLoop.h"
#include "VLS/Event/EventHandler.h"

#include <string>
#include <memory>
#include <map>
#include <io.h>

TEST(VLSEvent, EventLoop) {
    VLS::Event::EventLoop eventLoop;
    VLS::Event::EventHandler<> eventHandler;

    bool value = false;

    // Subscribe to events and using an event loop.
    // Event function will be trigger on the event loop.
    eventHandler.SubscribePersistent([&value]() { value = true; }, &eventLoop);
    EXPECT_FALSE(value);

    // Trigger the event will 
    eventHandler.Trigger();
    EXPECT_FALSE(value);

    eventLoop.Start();
    eventLoop.Stop();
    EXPECT_TRUE(value);
}

TEST(VLSEvent, EventLoop_ConstReference) {
    VLS::Event::EventLoop eventLoop;
    VLS::Event::EventHandler<const std::string&> eventHandler;

    std::string value = "value1";

    // Value has to match when function is triggered for references
    eventHandler.SubscribePersistent([](const std::string& v) { EXPECT_EQ(v, "value2"); });

    // Value is copied when function is Enqueued to the eventLoop when the event is triggered
    eventHandler.SubscribePersistent([](const std::string& v) { EXPECT_EQ(v, "value2"); }, &eventLoop);

    value = "value2";

    eventHandler.Trigger(value);
    value = "value3";

    // Call the function stored on the event loop
    eventLoop.Start();
    eventLoop.Stop();
}

TEST(VLSEvent, EventLoop_Pointer) {
    VLS::Event::EventLoop eventLoop;
    VLS::Event::EventHandler<std::string*> eventHandler;

    std::string value = "value1";

    // Value have to match when value is checked for pointers
    eventHandler.SubscribePersistent([](std::string* v) { EXPECT_EQ(*v, "value2"); });
    eventHandler.SubscribePersistent([](std::string* v) { EXPECT_EQ(*v, "value3"); }, &eventLoop);

    value = "value2";

    eventHandler.Trigger(&value);
    value = "value3";

    // Call the function stored on the event loop
    eventLoop.Start();
    eventLoop.Stop();
}
