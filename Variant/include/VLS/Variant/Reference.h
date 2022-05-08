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

#include <assert.h>

#include "VLS/Variant/Base.h"
#include "VLS/Convert/Functions.h"


namespace VLS::Variant {

class Value;

// =============================================================================
// Class definition
// =============================================================================
class Reference
{
public:
    Reference();
    Reference(const char *c);
    Reference(const bool &b);
    Reference(const int &i);
    Reference(const double &d);
    Reference(const std::string &s);
    Reference(const DateTime &dt);
    Reference(const Value &v);

    Reference(const Reference &copy);

    ~Reference();

    Reference& operator=(const Reference& copy);

    template<typename T>
    Reference& operator=(T value) { return *this = Reference(value); }

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

    int compare(const Reference& value, bool allowConversion = true, Convert::Settings* settings = nullptr) const;

    bool isEqual(const Reference& value, bool allowConversion = true, Convert::Settings* settings = nullptr) const;

    bool isNull() const;

    Type type() const;

    bool getBool() const;
    int getInt() const;
    double getDouble() const;
    const std::string& getCString() const;
    std::string& getString();
    const DateTime &getDateTime() const;

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
    PointerUnion r;
    Type t;

    friend class Value;
};

// =============================================================================
// (public)
template<typename T>
bool Reference::canGet(T &target, bool allowConversion, Convert::Settings * settings) const
{
    if (t == Type::Undefined) { return false; }
    if (!allowConversion && t != GetValueType(target)) { return false; }

    switch (t) {
        case Type::Undefined:
            return false;
        case Type::Char:
            return canConvert(target, r.c, settings);
        case Type::Bool:
            return canConvert(target, *r.b, settings);
        case Type::Integer:
            return canConvert(target, *r.i, settings);
        case Type::Double:
            return canConvert(target, *r.d, settings);
        case Type::String:
            return canConvert(target, *r.s, settings);
        case Type::DateTime:
            return canConvert(target, *r.dt, settings);
        default:
            assert(false);
            return false;
    }
    return false;
}

// =============================================================================
// (public)
template<typename T>
bool Reference::get(T &target, bool allowConversion, Convert::Settings * settings) const
{
    if (t == Type::Undefined) { return false; }
    if (!allowConversion && t != GetValueType(target)) { return false; }

    switch (t) {
        case Type::Undefined:
            return false;
        case Type::Char:
            return convert(target, r.c, settings);
        case Type::Bool:
            return convert(target, *r.b, settings);
        case Type::Integer:
            return convert(target, *r.i, settings);
        case Type::Double:
            return convert(target, *r.d, settings);
        case Type::String:
            return convert(target, *r.s, settings);
        case Type::DateTime:
            return convert(target, *r.dt, settings);
        default:
            assert(false);
            return false;
    }
    return false;
}

// =============================================================================
// (public)
template<typename T>
T Reference::value(bool allowConversion, Convert::Settings * settings) const
{
    T v;
    get(v, allowConversion, settings);
    return std::move(v);
}

} // namespace VLS::Variant

