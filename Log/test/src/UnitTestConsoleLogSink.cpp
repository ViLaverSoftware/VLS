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
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#pragma warning(pop)

#include <VLS/Log/ConsoleLogSink.h>
#include <VLS/Log/Log.h>
#include <VLS/Log/LogHandler.h>

#include <memory>

using ::testing::_;
using ::testing::StrictMock;

using namespace VLS::Log;

TEST(VLSConsoleLogSink, PrintVisualTest) {
  auto sink = std::make_shared<StrictMock<ConsoleLogSink>>();
  LogHandler::instance()->addLogSink(sink);

  const char* message = "Hello world!";

  VLS::logTrace(message);
  VLS::logDebug(message);
  VLS::logInfo(message);
  VLS::logWarning(message);
  VLS::logError(message);
  VLS::logCritical(message);
}
