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

#include <VLS/Converter/IConverterItem.h>

#include <functional>

namespace VLS::Converter {

/// <summary>
///
/// </summary>
/// <remarks>
///
/// </remarks>
template<typename T1, typename T2>
class ConverterItem: public IConverterItem {
public:
  ConverterItem( std::function<bool(const T1&, T2&, const char* )> func ): _func(func){}

  bool convert(const void *source, void *target, const char *properties) const;

  template< typename T3, typename T4>
  bool typeMatch() const {
    return std::is_same<T1, T3>::value && std::is_same<T2, T4>::value;
  }

  const type_info& sourceType() const override;
  const type_info& targetType() const override;

private:
  std::function<bool(const T1&, T2&, const char* )> _func;

};

template<typename T1, typename T2>
bool ConverterItem<T1, T2>::convert(const void *source, void *target, const char *properties) const
{
  return _func( *static_cast<const T1*> (source), *static_cast<T2*>(target), properties );
}

template<typename T1, typename T2>
const type_info& ConverterItem<T1, T2>::sourceType() const
{
  return typeid(T1);
}

template<typename T1, typename T2>
const type_info& ConverterItem<T1, T2>::targetType() const
{
  return typeid(T2);
}

}
