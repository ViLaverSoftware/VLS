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

#include <VLS/Converter/ConverterItem.h>
#include <VLS/Log/Log.h>

#include <format>
#include <functional>
#include <memory>
#include <string>
#include <vector>

using namespace VLS;

namespace VLS::Converter {

/**
 * @brief The Converter class can convert one data type to an other.
 * Funtions to convert one type to an other can be registered with the
 * addConverter function.
 */
class Converter {
 public:
  Converter() = default;

  /**
   * @brief addConverter
   * @param func
   * @return
   */
  template <typename T1, typename T2>
  bool addConverter(
      std::function<bool(const T1&, T2&, const std::string&)> func);

  /**
   * @brief addAsignmentConverter adds a converter from one type to the same
   * type.
   * It is needed when only a type and void pointer is known of both the
   * source and target.
   */
  template <typename T>
  void addAsignmentConverter();

  /**
   * @brief convert converts the source value to the target value.
   * The function finds and uses the matching converter function.
   * Use addConverter to add any needed converters.
   * @param source
   * @param target
   * @param format optional format string.
   * @return true if convertion is successfull, otherwise false.
   */
  template <typename T1, typename T2>
  bool convert(const T1& source, T2& target,
               const std::string& format = std::string()) const noexcept;

  template <typename T>
  bool convert(const char* source, T& target,
               const std::string& format = std::string()) const noexcept;

  template <typename T1, typename T2>
  T1 convert(const T2& source, const std::string& format = std::string()) const;

  template <typename T>
  T convert(const char* source,
            const std::string& format = std::string()) const;

  template <typename T1, typename T2>
  bool hasConverter() const noexcept;

  template <const char*, typename T>
  bool hasConverter() const noexcept;

 private:
  template <typename T>
  T convert(const type_info& sourceType, const void* sourceValue,
            const std::string& format = std::string()) const;

  bool convert(const type_info& sourceType, const void* sourceValue,
               const type_info& targetType, void* targetValue,
               const std::string& format) const noexcept;

  /**
   * @brief getConverterItem Return the converter item with matching source and
   * target types. Return nullptr if it do not exist.
   */
  IConverterItem* getConverterItem(const type_info& sourceType,
                                   const type_info& targetType) const noexcept;

  std::vector<std::unique_ptr<IConverterItem>> _converterItems;

  friend class ValueConverter;
};
// Implementation

template <typename T1, typename T2>
bool Converter::addConverter(
    std::function<bool(const T1&, T2&, const std::string&)> func) {
  auto converterItem = std::make_unique<ConverterItem<T1, T2>>(func);

  addAsignmentConverter<T2>();

  // Check if converter already exists
  auto it = std::find_if(std::begin(_converterItems), std::end(_converterItems),
                         [=](const std::unique_ptr<IConverterItem>& item) {
                           return typeid(T1) == item->sourceType() &&
                                  typeid(T2) == item->targetType();
                         });

  if (it == std::end(_converterItems)) {
    // Add new converter
    logTrace(std::format("Adding new from \"{}\" to \"{}\" converter",
                         typeid(T1).name(), typeid(T2).name()));
    _converterItems.push_back(std::move(converterItem));
    return true;
  } else {
    // Replace existing converter
    *it = std::move(converterItem);
    logWarning(std::format("Replacing existing from \"{}\" to \"{}\" converter",
                           typeid(T1).name(), typeid(T2).name()));
    return false;
  }
}

template <typename T>
void Converter::addAsignmentConverter() {
  if (!hasConverter<T, T>()) {
    _converterItems.push_back(std::make_unique<ConverterItem<T, T>>(
        [](const T& source, T& target, const std::string&) {
          target = source;
          return true;
        }));
  }
}

template <typename T1, typename T2>
bool Converter::convert(const T1& source, T2& target,
                        const std::string& format) const noexcept {
  return convert(typeid(T1), &source, typeid(T2), &target, format);
}

template <typename T>
bool Converter::convert(const char* source, T& target,
                        const std::string& format) const noexcept {
  return convert(std::string(source), &target, format);
}

template <typename T1, typename T2>
T1 Converter::convert(const T2& source, const std::string& format) const {
  return convert<T1>(typeid(T2), &source, format);
}

template <typename T>
T Converter::convert(const char* source, const std::string& format) const {
  return convert<T>(std::string(source), format);
}

template <typename T>
T Converter::convert(const type_info& sourceType, const void* sourceValue,
                     const std::string& format) const {
  // Return a copy of the source if values are equal
  if (sourceType == typeid(T)) {
    return *static_cast<const T*>(sourceValue);
  }

  const IConverterItem* converterItem = getConverterItem(sourceType, typeid(T));
  if (!converterItem) {
    auto errorText = std::format("No converter from \"{}\" to \"{}\"",
                                 sourceType.name(), typeid(T).name());
    logError(errorText);
    throw std::exception(errorText.c_str());
  }

  T value;
  if (converterItem->convert(sourceValue, &value, format)) {
    return value;
  }
  auto errorText = std::string("Failed to convert ") + sourceType.name() +
                   " to " + typeid(T).name();
  logError(errorText);
  throw std::exception(errorText.c_str());
}

template <typename T1, typename T2>
bool Converter::hasConverter() const noexcept {
  return getConverterItem(typeid(T1), typeid(T2)) != nullptr;
}

template <const char*, typename T2>
bool Converter::hasConverter() const noexcept {
  return getConverterItem(typeid(std::string), typeid(T2)) != nullptr;
}

}  // namespace VLS::Converter
