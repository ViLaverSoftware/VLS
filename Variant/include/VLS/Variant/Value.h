/*
 * OakModelView (http://oakmodelview.com/)
 * Author: Mikkel Nøhr Løvgreen (mikkel@oakmodelview.com)
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

#include "VLS/Variant/Base.h"
#include "VLS/Variant/Reference.h"
#include "VLS/Convert/Settings.h"
#include "VLS/Convert/Functions.h"


namespace VLS::Variant {

// =============================================================================
// Class definition
// =============================================================================
class Value
{
public:
    Value();
    Value(const char *c);
    Value(bool b);
    Value(int i);
    Value(double d);
    Value(const std::string &s);
    Value(const DateTime &dt);
    Value(Type type);

    Value(const Reference& uRef);

    Value(const Value& copy);
    Value(Value&& move) noexcept;

    ~Value();

    Value& operator=(const Reference& value);
    Value& operator=(const Value& copy);
    Value& operator=(Value&& move) noexcept;

    template<typename T>
    Value& operator=(T value) { return *this = Reference(value); }

    operator bool() const;

    bool operator==(const Reference& value) const;
    bool operator!=(const Reference& value) const;

    bool operator>(const Reference& value) const;
    bool operator>=(const Reference& value) const;
    bool operator<(const Reference& value) const;
    bool operator<=(const Reference& value) const;

    template<typename T>
    bool operator==(T value) const { return *this == Reference(value); }
    template<typename T>
    bool operator!=(T value) const { return *this != Reference(value); }

    template<typename T>
    bool operator>(T value) const { return *this > Reference(value); }
    template<typename T>
    bool operator>=(T value) const { return *this >= Reference(value); }
    template<typename T>
    bool operator<(T value) const { return *this < Reference(value); }
    template<typename T>
    bool operator<=(T value) const { return *this <= Reference(value); }

    int compare(const Reference& value, bool allowConversion = false, Convert::Settings* settings = nullptr) const;

    bool isEqual(const Reference& value, bool allowConversion = true, Convert::Settings* settings = nullptr) const;

    bool isNull() const;

    Type type() const;

    const Reference getRef() const;
    Reference getRef();

    bool getBool() const;
    int getInt() const;
    double getDouble() const;
    const std::string& getCString() const;
    std::string& getString();

    template<typename T>
    bool canGet(T& target, bool allowConversion = true, Convert::Settings* settings = nullptr) const;
    template<typename T>
    bool get(T& target, bool allowConversion = true, Convert::Settings* settings = nullptr) const;

    bool canGet(Reference& target, bool allowConversion = true, Convert::Settings* settings = nullptr) const;
    bool get(Reference& target, bool allowConversion = true, Convert::Settings* settings = nullptr) const;

    bool canGet(Value& target, bool allowConversion = true, Convert::Settings* settings = nullptr) const;
    bool get(Value& target, bool allowConversion = true, Convert::Settings* settings = nullptr) const;

    template<typename T>
    T value(bool allowConversion = true, Convert::Settings* settings = nullptr) const;

protected:
    ValueUnion v;
    Type t;

    friend class Reference;
};

// =============================================================================
// (public)
template<typename T>
bool Value::canGet(T &target, bool allowConversion, Convert::Settings * settings) const
{
    Reference sourceRef(*this);
    return sourceRef.canGet(target, allowConversion, settings);
}

// =============================================================================
// (public)
template<typename T>
bool Value::get(T &target, bool allowConversion, Convert::Settings * settings) const
{
    Reference sourceRef(*this);
    return sourceRef.get(target, allowConversion, settings);
}

// =============================================================================
// (public)
template<typename T>
T Value::value(bool allowConversion, Convert::Settings * settings) const
{
    T v;
    get(v, allowConversion, settings);
    return std::move(v);
}

typedef std::vector<Value> UnionValueList;

} // namespace VLS::Variant

