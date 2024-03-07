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

#include <VLS/Properties/Property.h>

#include <VLS/Log/Log.h>
#include <VLS/Log/LogHandler.h>
#include <VLS/Log/ConsoleLogSink.h>

using namespace VLS::Properties;

TEST(VLSProperties, Test) {
  auto consoleSink = std::make_shared<Log::ConsoleLogSink>();
  Log::LogHandler::instance()->addLogSink( consoleSink );

  Property<std::string> property;
  EXPECT_EQ(property.value(), "");

  property.set("42");
  EXPECT_EQ(property.value(), "42");
  EXPECT_EQ(property.value<int>(), 42);
}

TEST(VLSProperties, ChangedEvent) {
  std::string testValue;
  Property<std::string> property;
  property.changed.SubscribePersistent([&testValue]( const std::string& value) {
    testValue = value;
  });

  property.set(std::string("Hej"));
  EXPECT_EQ(testValue, "Hej");
}
