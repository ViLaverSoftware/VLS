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

#include "VLS/Variant/Reference.h"
#include "VLS/Variant/Value.h"


#include "VLS/Utilities/Assert.h"


namespace VLS::Variant {

// =============================================================================
// (public)
Reference::Reference()
    : t(Type::Undefined)
{
    r.i = nullptr;
}

// =============================================================================
// (public)
Reference::Reference(const char *c)
    : t(Type::Char)
{
    r.c = c;
}

// =============================================================================
// (public)
Reference::Reference(const bool &b)
    : t(Type::Bool)
{
    r.b = const_cast<bool*>(&b);
}

// =============================================================================
// (public)
Reference::Reference(const int &i)
    : t(Type::Integer)
{
    r.i = &i;
}

// =============================================================================
// (public)
Reference::Reference(const double &d)
    : t(Type::Double)
{
    r.d = &d;
}

// =============================================================================
// (public)
Reference::Reference(const std::string &s)
    : t(Type::String)
{
    r.s = &s;
}

// =============================================================================
// (public)
Reference::Reference(const DateTime &dt)
    : t(Type::DateTime)
{
    r.dt = &dt;
}

// =============================================================================
// (public)
Reference::Reference(const Value &v)
    : t(v.type())
{
    if (t == Type::Undefined) {
       r.i = nullptr;
    } else if (t == Type::Bool) {
        r.b = const_cast<bool*>(&v.v.b);
    } else if (t == Type::Integer) {
        r.i = const_cast<int*>(&v.v.i);
    } else if (t == Type::Double) {
        r.d = const_cast<double*>(&v.v.d);
    } else if (t == Type::String) {
        r.s = v.v.s;
    } else if (t == Type::DateTime) {
        r.dt = v.v.dt;
    } else {
        ASSERT(false);
    }
}

// =============================================================================
// (public)
Reference::Reference(const Reference &copy)
    : t(copy.t)
{
    memcpy(&r, &copy.r, sizeof(r));
}

// =============================================================================
// (public)
Reference::~Reference()
{

}

// =============================================================================
// (public)
Reference &Reference::operator=(const Reference &copy)
{
    bool result = copy.get(*this);
    ASSERT(result);
    return *this;
}

// =============================================================================
// (public)
bool Reference::operator==(const Reference &value) const
{
    return compare(value, false) == 0;
}

// =============================================================================
// (public)
bool Reference::operator!=(const Reference &value) const
{
    return compare(value, false) != 0;
}

// =============================================================================
// (public)
bool Reference::operator>(const Reference &value) const
{
    return compare(value, false) > 0;
}

// =============================================================================
// (public)
bool Reference::operator>=(const Reference &value) const
{
    return compare(value, false) >= 0;
}

// =============================================================================
// (public)
bool Reference::operator<(const Reference &value) const
{
    return compare(value, false) < 0;
}

// =============================================================================
// (public)
bool Reference::operator<=(const Reference &value) const
{
    return compare(value, false) <= 0;
}

// =============================================================================
// (public)
int Reference::compare(const Reference& value, bool allowConversion, Convert::Settings* settings) const
{
    if (GetValueType(t) != GetValueType(value.t)) {
        if (!allowConversion) { return -1000; }

        Value uValue(*this);
        Reference uRef(uValue);

        if (!value.get(uRef, allowConversion, settings)) { return -1000; }
        return compare(uRef, false);
    }

    switch (t) {
        case Type::Undefined:
            return 0;
        case Type::Bool:
            return (*r.b == *value.r.b) ? 0 : (*r.b) ? 1 : -1;
        case Type::Integer:
            return (*r.i == *value.r.i) ? 0 : (*r.i > *value.r.i) ? 1 : -1;
        case Type::Double:
            return (std::abs(*r.d - *value.r.d) < 1.0e-8) ? 0 : (*r.d > *value.r.d) ? 1 : -1;
        case Type::String:
            if (value.t == Type::String) {
                return r.s->compare(*value.r.s);
            } else {
                return r.s->compare(value.r.c);
            }
        case Type::Char:
            if (value.t == Type::String) {
                return std::strcmp(r.c, value.r.s->c_str());
            } else {
                return std::strcmp(r.c, value.r.c);
            }
        case Type::DateTime:
            return *r.dt == *value.r.dt ? 0 : (*r.dt < *value.r.dt) ? -1 : 1;
        default:
            ASSERT(false);
    }
    return -1000;
}

// =============================================================================
// (public)
bool Reference::isEqual(const Reference &value, bool allowConversion, Convert::Settings * settings) const
{
    return compare(value, allowConversion, settings) == 0;
}

// =============================================================================
// (public)
bool Reference::isNull() const
{
    return t == Type::Undefined;
}

// =============================================================================
// (public)
Type Reference::type() const
{
    return t;
}

// =============================================================================
// (public)
bool Reference::getBool() const
{
    ASSERT(t == Type::Bool);
    return *r.b;
}

// =============================================================================
// (public)
int Reference::getInt() const
{
    ASSERT(t == Type::Integer);
    return *r.i;
}

// =============================================================================
// (public)
double Reference::getDouble() const
{
    ASSERT(t == Type::Double);
    return *r.d;
}

// =============================================================================
// (public)
const std::string& Reference::getCString() const
{
    ASSERT(t == Type::String);
    return *r.s;
}

// =============================================================================
// (public)
std::string &Reference::getString()
{
    ASSERT(t == Type::String);
    return *const_cast<std::string*>(r.s);
}

// =============================================================================
// (public)
const DateTime &Reference::getDateTime() const
{
    ASSERT(t == Type::DateTime);
    return *r.dt;
}

// =============================================================================
// (public)
bool Reference::canGet(Reference &target, bool allowConversion, Convert::Settings *settings) const
{
    if (t == Type::Undefined) { return false; }
    if (!allowConversion && target.t != t) { return false; }

    switch (target.t) {
        case Type::Undefined:
            return false;
        case Type::Char:
            return false;
        case Type::Bool:
            return canGet(*const_cast<bool*>(target.r.b), allowConversion, settings);
        case Type::Integer:
            return canGet(*const_cast<int*>(target.r.i), allowConversion, settings);
        case Type::Double:
            return canGet(*const_cast<double*>(target.r.d), allowConversion, settings);
        case Type::String:
            return canGet(*const_cast<std::string*>(target.r.s), allowConversion, settings);
        case Type::DateTime:
            return canGet(*const_cast<DateTime*>(target.r.dt), allowConversion, settings);
        default:
            ASSERT(false);
            return false;
    }
}

// =============================================================================
// (public)
bool Reference::get(Reference &target, bool allowConversion, Convert::Settings * settings) const
{
    if (t == Type::Undefined) { return false; }
    if (!allowConversion && target.t != t) { return false; }

    switch (target.t) {
        case Type::Undefined:
            return false;
        case Type::Char:
            return false;
        case Type::Bool:
            return get(*const_cast<bool*>(target.r.b), allowConversion, settings);
        case Type::Integer:
            return get(*const_cast<int*>(target.r.i), allowConversion, settings);
        case Type::Double:
            return get(*const_cast<double*>(target.r.d), allowConversion, settings);
        case Type::String:
            return get(*const_cast<std::string*>(target.r.s), allowConversion, settings);
        case Type::DateTime:
            return get(*const_cast<DateTime*>(target.r.dt), allowConversion, settings);
        default:
            ASSERT(false);
            return false;
    }
}

// =============================================================================
// (public)
bool Reference::canGet(Value &target, bool allowConversion, Convert::Settings * settings) const
{
    Reference uRef(target);
    return canGet(uRef, allowConversion, settings);
}

// =============================================================================
// (public)
bool Reference::get(Value &target, bool allowConversion, Convert::Settings * settings) const
{
    Reference uRef(target);
    return get(uRef, allowConversion, settings);
}

} // namespace VLS::Variant

