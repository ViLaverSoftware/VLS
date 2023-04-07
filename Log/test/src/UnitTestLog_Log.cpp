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
#include <gmock/gmock.h>
#pragma warning(pop)

#include <VLS/Log/Log.h>
#include <VLS/Log/LogHandler.h>

#include <LogSinkMock.h>

#include <memory>

using ::testing::StrictMock;
using ::testing::_;

using namespace VLS::Log;

TEST(VLSLog, NoLogSink)
{
  const char* message = "Hello world!";
  VLS::logInfo( message );
}

TEST(VLSLog, LogSinkMessage)
{
  auto mockSink = std::make_shared<StrictMock<LogSinkMock>>();
  LogHandler::instance()->addLogSink(mockSink);

  const char* message = "Hello world!";

#ifdef __cpp_lib_source_location
  EXPECT_CALL(*mockSink, privateLog(LogLevel::Trace, message,_)).Times(1);
#else
  EXPECT_CALL(*mockSink, privateLog(LogLevel::Trace, message)).Times(1);
#endif
  VLS::logTrace( message );

#ifdef __cpp_lib_source_location
  EXPECT_CALL(*mockSink, privateLog(LogLevel::Debug, message,_)).Times(1);
#else
  EXPECT_CALL(*mockSink, privateLog(LogLevel::Debug, message)).Times(1);
#endif
  VLS::logDebug( message );

#ifdef __cpp_lib_source_location
  EXPECT_CALL(*mockSink, privateLog(LogLevel::Info, message,_)).Times(1);
#else
  EXPECT_CALL(*mockSink, privateLog(LogLevel::Info, message)).Times(1);
#endif
  VLS::logInfo( message );

#ifdef __cpp_lib_source_location
  EXPECT_CALL(*mockSink, privateLog(LogLevel::Warning, message,_)).Times(1);
#else
  EXPECT_CALL(*mockSink, privateLog(LogLevel::Warning, message)).Times(1);
#endif
  VLS::logWarning( message );

#ifdef __cpp_lib_source_location
  EXPECT_CALL(*mockSink, privateLog(LogLevel::Error, message,_)).Times(1);
#else
  EXPECT_CALL(*mockSink, privateLog(LogLevel::Error, message)).Times(1);
#endif
  VLS::logError( message );

#ifdef __cpp_lib_source_location
  EXPECT_CALL(*mockSink, privateLog(LogLevel::Critical, message,_)).Times(1);
#else
  EXPECT_CALL(*mockSink, privateLog(LogLevel::Critical, message)).Times(1);
#endif
  VLS::logCritical( message );
}

TEST(VLSLog, LogSinkDestroyed)
{
  {
    auto mockSink = std::make_shared<StrictMock<LogSinkMock>>();
    LogHandler::instance()->addLogSink(mockSink);
  }

  const char* message = "Hello world!";
  VLS::logTrace( message );
}
