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

#include <VLS/Converter/ValueConverter.h>

namespace VLS::Properties {

/// <summary>
///
/// </summary>
/// <remarks>
///
/// </remarks>

class IProperty {
public:
  template<typename T>
  IProperty(T& value);

  virtual ~IProperty() = default;



  template<typename T>
  bool get(T& value) const;

  template<typename T>
  bool set(const T& value);

protected:
  Converter::ValueConverter m_valueConverter;
};

template<typename T>
IProperty::IProperty(T& value)
  : m_valueConverter(value)
{
}

template<typename T>
bool IProperty::get(T &value) const
{
  return m_valueConverter.get(value);
}

template<typename T>
bool IProperty::set(const T &value)
{
  return m_valueConverter.set(value);
}

}
