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

#pragma warning(push, 0)
#include <gmock/gmock.h>
#pragma warning(pop)

#include <VLS/Log/AbstractLogSink.h>

namespace VLS::Log {
class LogSinkMock : public AbstractLogSink {
 public:
  MOCK_METHOD(std::string, name, (), (const, override));
#ifdef __cpp_lib_source_location
  MOCK_METHOD(void, privateLog,
              (LogLevel, const std::string&, const std::source_location),
              (const, override));
#else
  MOCK_METHOD(void, privateLog, (LogLevel, const std::string&),
              (const, override));
#endif
};
}  // namespace VLS::Log
