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

#include <VLS/Converter/ConverterFactory.h>
#include <VLS/Log/ConsoleLogSink.h>
#include <VLS/Log/Log.h>
#include <VLS/Log/LogHandler.h>

using namespace VLS::Converter;
using namespace VLS;

TEST(VLSConverter, DevelopmentTests) {
  auto consoleSink = std::make_shared<Log::ConsoleLogSink>();
  Log::LogHandler::instance()->addLogSink(consoleSink);

  ConverterPtr converter = ConverterFactory::defaultConverter();

  std::string result;
  std::string expectedResult = "42";
  int source = 42;

  converter->convert(source, result);

  EXPECT_EQ(result, expectedResult);

  int intResult;
  std::string strSource = "-17";
  converter->convert(strSource, intResult);

  EXPECT_EQ(intResult, -17);

  bool r = converter->hasConverter<int, const char*>();
  EXPECT_FALSE(r);

  auto str = converter->convert<std::string>(26);
  EXPECT_EQ(str, "26");

  bool addResult = converter->addConverter<int, std::string>(
      [](const int& source, std::string& target, const std::string&) {
        target = std::to_string(source) + "Int";
        return true;
      });
  EXPECT_FALSE(addResult);

  str = converter->convert<std::string>(26);
  EXPECT_EQ(str, "26Int");

  str = converter->convert<std::string>("MikkelNL");
  EXPECT_EQ(str, "MikkelNL");

  str = converter->convert<std::string>(std::string("asignment"));
  EXPECT_EQ(str, "asignment");

  str = converter->convert<std::string>(3.141f, ":10.2f");
  EXPECT_EQ(str, "      3.14");

  str = converter->convert<std::string>(3.141, ":.2f");
  EXPECT_EQ(str, "3.14");
}
