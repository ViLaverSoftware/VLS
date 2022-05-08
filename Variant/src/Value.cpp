/*
 * VLS (http://vilaversoftware.dk/)
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

#include "VLS/Variant/Value.h"

#include "VLS/Variant/Reference.h"
#include "VLS/Convert/Functions.h"


#include "VLS/Utilities/Assert.h"


namespace VLS::Variant {

// =============================================================================
// (public)
Value::Value()
    : t(Type::Undefined)
{
    v.i = 0;
}

// =============================================================================
// (public)
Value::Value(const char *c)
    : t(Type::String)
{
    v.s = new std::string(c);
}

// =============================================================================
// (public)
Value::Value(bool b)
    : t(Type::Bool)
{
    v.b = b;
}

// =============================================================================
// (public)
Value::Value(int i)
    : t(Type::Integer)
{
    v.i = i;
}

// =============================================================================
// (public)
Value::Value(double d)
    : t(Type::Double)
{
    v.d = d;
}

// =============================================================================
// (public)
Value::Value(const std::string &s)
    : t(Type::String)
{
    v.s = new std::string(s);
}

// =============================================================================
// (public)
Value::Value(const DateTime &dt)
    : t(Type::DateTime)
{
    v.dt = new DateTime(dt);
}

// =============================================================================
// (public)
Value::Value(Type type)
    : t(type)
{
    ASSERT(static_cast<int>(type) > 0);
    if (type == Type::String) {
        v.s = new std::string();
    } else if (type == Type::DateTime) {
        v.dt = new DateTime(DateTime::defaultDateTime());
    } else {
        v.i = 0;
    }
}

// =============================================================================
// (public)
Value::Value(const Reference &uRef)
{
    *this = uRef;
}

// =============================================================================
// (public)
Value::Value(const Value &copy)
    : t(Type::Undefined)
{
    *this = copy;
}

// =============================================================================
// (public)
Value::Value(Value &&move) noexcept
    : t(Type::Undefined)
{
    *this = std::move(move);
}

// =============================================================================
// (public)
Value::~Value()
{
    if (t == Type::String) {
        delete v.s;
        v.s = nullptr;
    } else if (t == Type::DateTime) {
        delete v.dt;
        v.dt = nullptr;
    }
}

// =============================================================================
// (public)
Value &Value::operator=(const Reference &value)
{
    if (t == Type::String) {
        if (value.t == Type::String) {
            *v.s = *value.r.s;
            return *this;
        } else {
            delete v.s;
        }
    }

    if (t == Type::DateTime) {
        if (value.t == Type::DateTime) {
            *v.dt = *value.r.dt;
            return *this;
        } else {
            delete v.dt;
        }
    }

    t = value.t;
    switch (value.t) {
        case Type::Undefined:
            v.i = 0;
            break;
        case Type::Char:
            v.s = new std::string(value.r.c);
            t = Type::String;
            break;
        case Type::Bool:
            v.b = *value.r.b;
            break;
        case Type::Integer:
            v.i = *value.r.i;
            break;
        case Type::Double:
            v.d = *value.r.d;
            break;
        case Type::String:
            v.s = new std::string(*value.r.s);
            break;
        case Type::DateTime:
            v.dt = new DateTime(*value.r.dt);
            break;
        default:
            ASSERT(false);
    }

    return *this;
}

// =============================================================================
// (public)
Value &Value::operator=(const Value &copy)
{
    Reference uRef(copy);
    return *this = uRef;
}

// =============================================================================
// (public)
bool Value::operator==(const Reference &value) const
{
    Reference uRef(*this);
    return uRef == value;
}

// =============================================================================
// (public)
bool Value::operator!=(const Reference &value) const
{
    Reference uRef(*this);
    return uRef != value;
}

// =============================================================================
// (public)
bool Value::operator>=(const Reference &value) const
{
    Reference uRef(*this);
    return uRef >= value;
}

// =============================================================================
// (public)
bool Value::operator>(const Reference &value) const
{
    Reference uRef(*this);
    return uRef > value;
}

// =============================================================================
// (public)
bool Value::operator<(const Reference &value) const
{
    Reference uRef(*this);
    return uRef < value;
}

// =============================================================================
// (public)
bool Value::operator<=(const Reference &value) const
{
    Reference uRef(*this);
    return uRef <= value;
}

// =============================================================================
// (public)
int Value::compare(const Reference &value, bool allowConversion, Convert::Settings * settings) const
{
    Reference uRef(*this);
    return uRef.compare(value, allowConversion, settings);
}

// =============================================================================
// (public)
bool Value::isEqual(const Reference &value, bool allowConversion, Convert::Settings * settings) const
{
    Reference uRef(*this);
    return uRef.isEqual(value, allowConversion, settings);
}

// =============================================================================
// (public)
bool Value::isNull() const
{
    return t == Type::Undefined;
}

// =============================================================================
// (public)
Value &Value::operator=(Value &&move) noexcept
{
    if (t == Type::String) {
        delete v.s;
    } else if (t == Type::DateTime) {
        delete v.dt;
    }
    t = move.t;
    memcpy(&v, &move.v, sizeof(v));

    move.t = Type::Undefined;
    move.v.s = nullptr;

    return *this;
}

// =============================================================================
// (public)
Value::operator bool() const
{
    switch (t) {
        case Type::Undefined:
            ASSERT(false);
            return false;
        case Type::Bool:
            return v.b;
        case Type::Integer:
            return v.i != 0;
        case Type::Double:
            return v.d != 0.0;
        case Type::String:
            return !v.s->empty();
        case Type::DateTime:
            return true;
        default:
            ASSERT(false);
    }
    return false;
}

// =============================================================================
// (public)
Type Value::type() const
{
    return t;
}

// =============================================================================
// (public)
const Reference Value::getRef() const
{
    return Reference(*this);
}

// =============================================================================
// (public)
Reference Value::getRef()
{
    return Reference(*this);
}

// =============================================================================
// (public)
bool Value::getBool() const
{
    ASSERT(t == Type::Bool);
    return v.b;
}

// =============================================================================
// (public)
int Value::getInt() const
{
    ASSERT(t == Type::Integer);
    return v.i;
}

// =============================================================================
// (public)
double Value::getDouble() const
{
    ASSERT(t == Type::Double);
    return v.d;
}

// =============================================================================
// (public)
const std::string& Value::getCString() const
{
    ASSERT(t == Type::String);
    return *v.s;
}

// =============================================================================
// (public)
std::string& Value::getString()
{
    ASSERT(t == Type::String);
    return *v.s;
}

// =============================================================================
// (public)
bool Value::canGet(Reference &target, bool allowConversion, Convert::Settings * settings) const
{
    Reference sourceRef(*this);
    return sourceRef.canGet(target, allowConversion, settings);
}

// =============================================================================
// (public)
bool Value::get(Reference &target, bool allowConversion, Convert::Settings * settings) const
{
    Reference sourceRef(*this);
    return sourceRef.get(target, allowConversion, settings);
}

// =============================================================================
// (public)
bool Value::canGet(Value &target, bool allowConversion, Convert::Settings * settings) const
{
    Reference sourceRef(*this);
    Reference targetRef(target);
    return sourceRef.canGet(targetRef, allowConversion, settings);
}

// =============================================================================
// (public)
bool Value::get(Value &target, bool allowConversion, Convert::Settings * settings) const
{
    Reference sourceRef(*this);
    Reference targetRef(target);
    return sourceRef.get(targetRef, allowConversion, settings);
}

} // namespace VLS::Variant

