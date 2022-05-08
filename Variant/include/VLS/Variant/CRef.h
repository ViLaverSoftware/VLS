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

#include <string>

#include "VLS/Convert/Functions.h"
#include "VLS/Variant/Type.h"
#include "VLS/DateTime.h"

namespace VLS::Variant {

//class Value;
class Ref;
class Val;

// =============================================================================
// Class definition
// =============================================================================
class CRef
{
public:
    CRef();
    CRef(const char* _c);
    CRef(const bool& _b);
    CRef(const int& _i);
    CRef(const double& _d);
    CRef(const std::string& _s);
    CRef(const DateTime& _dt);

    CRef(const CRef& copy);

    virtual ~CRef();

    bool operator=(const CRef& value) = delete;

    bool operator==(const CRef& value) const;
    bool operator!=(const CRef& value) const;

    bool operator>(const CRef& value) const;
    bool operator>=(const CRef& value) const;
    bool operator<(const CRef& value) const;
    bool operator<=(const CRef& value) const;

    template<typename T>
    bool operator==(T value) const { return *this == CRef(value); }
    template<typename T>
    bool operator!=(T value) const { return *this != CRef(value); }
    template<typename T>
    bool operator>(T value) const { return *this > CRef(value); }
    template<typename T>
    bool operator>=(T value) const { return *this >= CRef(value); }
    template<typename T>
    bool operator<(T value) const { return *this < CRef(value); }
    template<typename T>
    bool operator<=(T value) const { return *this <= CRef(value); }

    int compare(const CRef& value, bool allowConversion = true, Convert::Settings* settings = nullptr) const;

    bool isEqual(const CRef& value, bool allowConversion = true, Convert::Settings* settings = nullptr) const;

    bool isNull() const;

    Type type() const;

    bool getBool() const;
    int getInt() const;
    double getDouble() const;
    const char* getCString() const;
    const std::string& getString() const;
    const DateTime& getDateTime() const;

    bool canGet(Ref& target, bool allowConversion = true, Convert::Settings* settings = nullptr) const;
    bool get(Ref& target, bool allowConversion = true, Convert::Settings* settings = nullptr) const;

    bool canGet(Val& target, bool allowConversion = true, Convert::Settings* settings = nullptr) const;
    bool get(Val& target, bool allowConversion = true, Convert::Settings* settings = nullptr) const;

    template<typename T>
    bool canGet(T& target, bool allowConversion = true, Convert::Settings* settings = nullptr) const;
    template<typename T>
    bool get(T& target, bool allowConversion = true, Convert::Settings* settings = nullptr) const;

    template<typename T>
    T value(bool allowConversion = true, Convert::Settings* settings = nullptr) const;

protected:
    Type t;

    union {
        const char* c;
        bool* b;
        int* i;
        double* d;
        std::string* s;
        VLS::DateTime* dt;
    };
};

// =============================================================================
// (public)
template<typename T>
bool CRef::canGet(T& target, bool allowConversion, Convert::Settings* settings) const
{
    if (t == Type::Undefined) { return false; }
    if (!allowConversion && t != CRef(target).type()) { return false; }

    switch (t) {
    case Type::Undefined:
        return false;
    case Type::Char:
        return canConvert(target, c, settings);
    case Type::Bool:
        return canConvert(target, *b, settings);
    case Type::Integer:
        return canConvert(target, *i, settings);
    case Type::Double:
        return canConvert(target, *d, settings);
    case Type::String:
        return canConvert(target, *s, settings);
    case Type::DateTime:
        return canConvert(target, *dt, settings);
    default:
        assert(false);
        return false;
    }
    return false;
}

// =============================================================================
// (public)
template<typename T>
bool CRef::get(T& target, bool allowConversion, Convert::Settings* settings) const
{
    if (t == Type::Undefined) { return false; }
    if (!allowConversion && t != CRef(target).type()) { return false; }

    switch (t) {
    case Type::Undefined:
        return false;
    case Type::Char:
        return convert(target, c, settings);
    case Type::Bool:
        return convert(target, *b, settings);
    case Type::Integer:
        return convert(target, *i, settings);
    case Type::Double:
        return convert(target, *d, settings);
    case Type::String:
        return convert(target, *s, settings);
    case Type::DateTime:
        return convert(target, *dt, settings);
    default:
        assert(false);
        return false;
    }
    return false;
}

// =============================================================================
// (public)
template<typename T>
T CRef::value(bool allowConversion, Convert::Settings* settings) const
{
    T v;
    get(v, allowConversion, settings);
    return std::move(v);
}

} // namespace VLS::Variant
