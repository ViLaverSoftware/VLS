/*
 * Copyright 2020 Vilaversoftware IVS (http://vilaversoftware.dk/)
 * Author: Mikkel N?hr L?vgreen (ml@vilaversoftware.dk)
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
#include <VLS/Converter/ValueConverter.h>

namespace VLS::Converter {
bool ValueConverter::set(const char *value, const char *properties) noexcept {
  std::string strValue(value);
  return m_converter->convert(typeid(std::string), &strValue, m_valueTypeInfo,
                              m_valuePtr, properties);
}

const type_info &ValueConverter::type() const { return m_valueTypeInfo; }

}  // namespace VLS::Converter
