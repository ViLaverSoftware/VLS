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
#include <VLS/Converter/Converter.h>
#include <VLS/Log/Log.h>

using namespace VLS;

namespace VLS::Converter {

bool Converter::convert(const type_info &sourceType, const void *sourceValue,
                        const type_info &targetType, void *targetValue,
                        const char *properties) const noexcept {
  const IConverterItem *converterItem =
      getConverterItem(sourceType, targetType);
  if (!converterItem) {
    logError(std::format("No converter from {} to {}", sourceType.name(),
                         targetType.name()));
    return false;
  }
  try {
    return converterItem->convert(sourceValue, targetValue, properties);
  } catch (...) {
    logError(std::string("Failed to convert ") + sourceType.name() + " to " +
             targetType.name());
  }
  return false;
}

IConverterItem *VLS::Converter::Converter::Converter::getConverterItem(
    const type_info &sourceType, const type_info &targetType) const noexcept {
  auto it = std::find_if(
      std::begin(_converterItems), std::end(_converterItems),
      [&sourceType, &targetType](const std::unique_ptr<IConverterItem> &item) {
        return sourceType == item->sourceType() &&
               targetType == item->targetType();
      });
  return (it == _converterItems.end()) ? nullptr : it->get();
}

}  // namespace VLS::Converter
