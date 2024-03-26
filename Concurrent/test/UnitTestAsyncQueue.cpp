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
#include <gtest/gtest.h>
#pragma warning(pop)

#include <VLS/Concurrent/AsyncQueue.h>

#include <VLS/Log/ConsoleLogSink.h>
#include <VLS/Log/LogHandler.h>

#include <io.h>

TEST(VLSEventLoop, Contructor) {
  auto sink = std::make_shared<VLS::Log::ConsoleLogSink>();
  VLS::Log::LogHandler::instance()->addLogSink(sink);

  VLS::Concurrent::AsyncQueue asyncQueue("TestThread");
  bool value = false;
  asyncQueue.exec([&value]() {
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    value = true;
  });
  EXPECT_FALSE(value);
  asyncQueue.wait();
  EXPECT_TRUE(value);
}
