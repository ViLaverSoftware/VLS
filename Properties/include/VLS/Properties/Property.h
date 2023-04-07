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

#include <VLS/Converter/ValueConverter.h>
#include <VLS/Properties/IProperty.h>
#include <VLS/Event/EventHandler.h>

namespace VLS::Properties {

/// <summary>
///
/// </summary>
/// <remarks>
///
/// </remarks>
template<typename T>
class Property: public Converter::ValueConverter {

public:
  Property();

  const T& value() const;
  using Converter::ValueConverter::value;

  void get(T& value) const;
  using Converter::ValueConverter::get;

  void set(const T& value);

  Event::EventHandler<T> changed;

protected:
  T m_data;
};

template<typename T>
Property<T>::Property()
  : VLS::Converter::ValueConverter(m_data)
{

}

template<typename T>
const T &Property<T>::value() const
{
  return m_data;
}

template<typename T>
void Property<T>::get(T& value) const
{
  value = m_data;
}

template<typename T>
void Property<T>::set(const T& value)
{
  if (m_data != value) {
    m_data = value;
    changed.Trigger( m_data );
  }
}

}