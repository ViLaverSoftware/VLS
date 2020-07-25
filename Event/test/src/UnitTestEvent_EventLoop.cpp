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

#include <string>
#include <memory>
#include <map>
#include <io.h>

TEST(VLSEventLoop, Contructor) {
    VLS::Event::EventLoop eventLoop;
    bool value = false;
    eventLoop.Enqueue([&value]() { value = true; });
    EXPECT_FALSE(value);
    eventLoop.Start();
    eventLoop.Stop();
    EXPECT_TRUE(value);
}

TEST(VKSEventLoop, Test) {
    VLS::Event::EventLoop eventLoop;
}