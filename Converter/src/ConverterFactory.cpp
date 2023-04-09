/*
 * Copyright 2020 Vilaversoftware IVS (http://vilaversoftware.dk/)
 * Author: Mikkel N�hr L�vgreen (ml@vilaversoftware.dk)
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
#include "VLS/Converter/ConverterFactory.h"

#include <VLS/Log/Log.h>

#include <algorithm>
#include <cctype>
#include <format>
#include <string>

using namespace VLS::Log;

namespace VLS::Converter {

ConverterPtr ConverterFactory::newEmptyConverter() {
  return std::make_shared<Converter>();
}

void ConverterFactory::addDefaultConverterItems(ConverterPtr converter) {
  converter->addConverter<const char*, std::string>(
      [](const char* source, std::string& target, const std::string&) {
        target = source;
        return true;
      });

  converter->addConverter<std::string, int>(
      [](const std::string& source, int& target, const std::string&) {
        target = stoi(source);
        return true;
      });

  converter->addConverter<int, std::string>(
      [](const int& source, std::string& target, const std::string& format) {
        if (format.empty()) {
          target = std::to_string(source);
        } else {
          std::string temp = std::format("{{{}}}", format);
          target = std::vformat(temp, std::make_format_args(source));
        }
        return true;
      });

  converter->addConverter<std::string, float>(
      [](const std::string& source, float& target, const std::string&) {
        target = stof(source);
        return true;
      });

  converter->addConverter<float, std::string>(
      [](const float& source, std::string& target, const std::string& format) {
        if (format.empty()) {
          target = std::to_string(source);
        } else {
          std::string temp = std::format("{{{}}}", format);
          target = std::vformat(temp, std::make_format_args(source));
        }
        return true;
      });

  converter->addConverter<std::string, double>(
      [](const std::string& source, double& target, const std::string&) {
        target = stof(source);
        return true;
      });

  converter->addConverter<double, std::string>(
      [](const double& source, std::string& target, const std::string& format) {
        if (format.empty()) {
          target = std::to_string(source);
        } else {
          std::string temp = std::format("{{{}}}", format);
          target = std::vformat(temp, std::make_format_args(source));
        }
        return true;
      });

  converter->addConverter<std::string, bool>(
      [](const std::string& source, bool& target, const std::string&) {
        std::string s = source;
        std::transform(s.begin(), s.end(), s.begin(),
                       [](unsigned char c) { return std::tolower(c); });

        if (s == "true" || s == "1" || s == "yes") {
          target = true;
        } else {
          target = false;
        }
        return true;
      });

  converter->addConverter<bool, std::string>(
      [](const bool& source, std::string& target, const std::string&) {
        return source ? "true" : "false";
      });
}

ConverterPtr ConverterFactory::defaultConverter() {
  ConverterPtr converter;
  if (!converter) {
    converter = newEmptyConverter();
    addDefaultConverterItems(converter);
  }
  return converter;
}

}  // namespace VLS::Converter
