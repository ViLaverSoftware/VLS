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
#pragma once

#include <VLS/Converter/Converter.h>

#include <memory>

namespace VLS::Converter {

using ConverterPtr = std::shared_ptr<Converter>;

/// <summary>
///
/// </summary>
/// <remarks>
///
/// </remarks>
class ConverterFactory {
 public:
  static ConverterPtr newEmptyConverter();

  static void addDefaultConverterItems(ConverterPtr converter);

  static ConverterPtr defaultConverter();
};

}  // namespace VLS::Converter
