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
#include <VLS/Event/EventHandler.h>

namespace VLS::Properties {

using PropertyBase = Converter::ValueConverter;

template <typename T>
class Property : public PropertyBase {
 public:
  Property();
  virtual ~Property() = default;

  template <typename T2>
  Property<T>& operator=(const Property<T2>& other);

  Property<T>& operator=(const Property<T>& other);

  Property<T>& operator=(const T& other);

  Property<T>& operator=(const char* other);

  const T& value() const;
  using PropertyBase::value;

  void get(T& value) const;
  using PropertyBase::get;

  void set(const T& value);

  template <typename T2>
  bool set(const T2& value, const std::string& format = std::string()) noexcept;
  bool set(const char* value,
           const std::string& format = std::string()) noexcept;

  void bind(const Property<T>& other);

  template <typename T2>
  void bind(const Property<T2>& other);

  Event::IEventHandler<T>& changed() const;

 protected:
  T m_data;
  mutable Event::EventHandler<T> m_changed;
  Event::Subscriber m_subscriber;
};

template <typename T>
Property<T>::Property() : PropertyBase(m_data) {}

template <typename T>
template <typename T2>
Property<T>& Property<T>::operator=(const Property<T2>& other) {
  bind(other);
  return *this;
}

template <typename T>
Property<T>& Property<T>::operator=(const Property<T>& other) {
  bind(other);
  return *this;
}

template <typename T>
Property<T>& Property<T>::operator=(const T& _value) {
  set(_value);
  return *this;
}

template <typename T>
Property<T>& Property<T>::operator=(const char* other) {
  set(other);
  return *this;
}

template <typename T>
const T& Property<T>::value() const {
  return m_data;
}

template <typename T>
void Property<T>::get(T& value) const {
  value = m_data;
}

template <typename T>
void Property<T>::set(const T& value) {
  m_subscriber.UnsubscribeAll();
  if (m_data != value) {
    m_data = value;
    m_changed.Trigger(m_data);
  }
}

template <typename T>
template <typename T2>
bool Property<T>::set(const T2& value, const std::string& format) noexcept {
  m_subscriber.UnsubscribeAll();
  if (ValueConverter::set(value, format)) {
    m_changed.Trigger(m_data);
    return true;
  }
  return false;
}

template <typename T>
bool Property<T>::set(const char* value, const std::string& format) noexcept {
  return set(std::string(value), format);
}

template <typename T>
void Property<T>::bind(const Property<T>& other) {
  set(other.value());
  other.changed().Subscribe(m_subscriber, [this](const T& data) {
    if (m_data != data) {
      m_data = data;
      m_changed.Trigger(data);
    }
  });
}

template <typename T>
template <typename T2>
void Property<T>::bind(const Property<T2>& other) {
  set(other.value());
  other.m_changed.Subscribe(m_subscriber, [this](const T2& data) {
    if (ValueConverter::set(data)) {
      m_changed.Trigger(m_data);
    }
  });
}

template <typename T>
Event::IEventHandler<T>& Property<T>::changed() const {
  return m_changed;
}

}  // namespace VLS::Properties
