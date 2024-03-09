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

#include "ConverterFactory.h"

namespace VLS::Converter {

class ValueConverter {
 public:
  template <typename T>
  ValueConverter(T& value, ConverterPtr converter = ConverterPtr());

  template <typename T>
  T value(const std::string& format = std::string()) const;

  template <typename T>
  bool get(T& value, const std::string& format = std::string()) noexcept;

  template <typename T>
  bool set(const T& value, const std::string& format = std::string()) noexcept;

  bool set(const char* value,
           const std::string& format = std::string()) noexcept;

  const type_info& type() const;

 private:
  const type_info& m_valueTypeInfo;
  void* m_valuePtr;
  ConverterPtr m_converter;
};

template <typename T>
ValueConverter::ValueConverter(T& value, ConverterPtr converter)
    : m_valueTypeInfo{typeid(T)}, m_valuePtr{&value}, m_converter{converter} {
  if (!m_converter) {
    m_converter = ConverterFactory::defaultConverter();
  }
}

template <typename T>
T ValueConverter::value(const std::string& format) const {
  return m_converter->convert<T>(m_valueTypeInfo, m_valuePtr, format);
}

template <typename T>
bool ValueConverter::get(T& value, const std::string& format) noexcept {
  return m_converter->convert(m_valueTypeInfo, m_valuePtr, typeid(T), &value,
                              format);
}

template <typename T>
bool ValueConverter::set(const T& value, const std::string& format) noexcept {
  return m_converter->convert(typeid(T), &value, m_valueTypeInfo, m_valuePtr,
                              format);
}

}  // namespace VLS::Converter
