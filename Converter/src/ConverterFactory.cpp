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

#include <string>
#include <algorithm>
#include <cctype>

using namespace VLS::Log;

namespace VLS::Converter {

ConverterPtr ConverterFactory::newEmptyConverter()
{
  return std::make_shared<Converter>();
}

void ConverterFactory::addDefaultConverterItems(ConverterPtr converter)
{
  converter->addConverter<const char*, std::string>( [](const char* source, std::string& target, const char* )
  {
    target = source;
    return true;
  });

  converter->addConverter<std::string, int>( [](const std::string& source, int& target, const char*) {
    target = stoi(source);
    return true;
  } );

  converter->addConverter<int, std::string>( [](const int& source, std::string& target, const char*) {
    target = std::to_string(source);
    return true;
  } );

  converter->addConverter<std::string, bool>( [](const std::string& source, bool& target, const char*) {
    std::string s = source;
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c){ return std::tolower(c); });

    if ( s == "true" || s == "1" || s == "yes" ) {
      target = true;
    } else {
      target = false;
    }
    return true;
  });

  converter->addConverter<bool, std::string>( [](const bool& source, std::string& target, const char*) {
    return source ? "true" : "false";
  });
}

ConverterPtr ConverterFactory::defaultConverter()
{
  ConverterPtr converter;
  if (!converter) {
    converter = newEmptyConverter();
    addDefaultConverterItems(converter);
  }
  return converter;
}

}
