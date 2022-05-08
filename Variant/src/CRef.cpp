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

#include "VLS/Variant/CRef.h"


#include "VLS/Utilities/Assert.h"

#include "VLS/Variant/Val.h"

namespace VLS::Variant {

// =============================================================================
// (public)
CRef::CRef()
    : t(Type::Undefined), i(nullptr)
{
}

// =============================================================================
// (public)
CRef::CRef(const char* _c)
    : t(Type::Char), c(const_cast<char*>(_c))
{
}

// =============================================================================
// (public)
CRef::CRef(const bool& _b)
    : t(Type::Bool), b(const_cast<bool*>(&_b))
{
}

// =============================================================================
// (public)
CRef::CRef(const int& _i)
    : t(Type::Integer), i(const_cast<int*>(&_i))
{
}

// =============================================================================
// (public)
CRef::CRef(const double& _d)
    : t(Type::Double), d(const_cast<double*>(&_d))
{
}

// =============================================================================
// (public)
CRef::CRef(const std::string& _s)
    : t(Type::String), s(const_cast<std::string*>(&_s))
{
}

// =============================================================================
// (public)
CRef::CRef(const DateTime& _dt)
    : t(Type::DateTime), dt(const_cast<DateTime*>(&_dt))
{
}

// =============================================================================
// (public)
CRef::CRef(const CRef& copy)
    : t(copy.t), i(copy.i)
{
}

// =============================================================================
// (public)
CRef::~CRef()
{

}

// =============================================================================
// (public)
bool CRef::operator==(const CRef& value) const
{
    return compare(value, false) == 0;
}

// =============================================================================
// (public)
bool CRef::operator!=(const CRef& value) const
{
    return compare(value, false) != 0;
}

// =============================================================================
// (public)
bool CRef::operator>(const CRef& value) const
{
    return compare(value, false) > 0;
}

// =============================================================================
// (public)
bool CRef::operator>=(const CRef& value) const
{
    return compare(value, false) >= 0;
}

// =============================================================================
// (public)
bool CRef::operator<(const CRef& value) const
{
    return compare(value, false) < 0;
}

// =============================================================================
// (public)
bool CRef::operator<=(const CRef& value) const
{
    return compare(value, false) <= 0;
}

// =============================================================================
// (public)
int CRef::compare(const CRef& value, bool allowConversion, Convert::Settings* settings) const
{
    // TODO: Do this better!!
    if (t != value.t && 
        !(t == Type::Char && value.t == Type::String) &&
        !(t == Type::String && value.t == Type::Char)) {

        if (!allowConversion) { return -1000; }

        Val uValue(*this);

        if (!value.get(uValue, allowConversion, settings)) { return -1000; }
        return compare(uValue, false);
    }

    switch (t) {
    case Type::Undefined:
        return 0;
    case Type::Bool:
        return (*b == *value.b) ? 0 : (*b) ? 1 : -1;
    case Type::Integer:
        return (*i == *value.i) ? 0 : (*i > * value.i) ? 1 : -1;
    case Type::Double:
        return (std::abs(*d - *value.d) < 1.0e-8) ? 0 : (*d > * value.d) ? 1 : -1;
    case Type::String:
        if (value.t == Type::String) {
            return s->compare(*value.s);
        }
        else {
            return s->compare(value.c);
        }
    case Type::Char:
        if (value.t == Type::String) {
            return std::strcmp(c, value.s->c_str());
        }
        else {
            return std::strcmp(c, value.c);
        }
    case Type::DateTime:
        return *dt == *value.dt ? 0 : (*dt < *value.dt) ? -1 : 1;
    default:
        ASSERT(false);
    }
    return -1000;
}

// =============================================================================
// (public)
bool CRef::isEqual(const CRef& value, bool allowConversion, Convert::Settings* settings) const
{
    return compare(value, allowConversion, settings) == 0;
}

// =============================================================================
// (public)
bool CRef::isNull() const
{
    return t == Type::Undefined;
}

// =============================================================================
// (public)
Type CRef::type() const
{
    return t;
}

// =============================================================================
// (public)
bool CRef::getBool() const
{
    ASSERT(t == Type::Bool);
    return *b;
}

// =============================================================================
// (public)
int CRef::getInt() const
{
    ASSERT(t == Type::Integer);
    return *i;
}

// =============================================================================
// (public)
double CRef::getDouble() const
{
    ASSERT(t == Type::Double);
    return *d;
}

// =============================================================================
// (public)
const char* CRef::getCString() const
{
    ASSERT(t == Type::Char);
    return c;
}

// =============================================================================
// (public)
const std::string& CRef::getString() const
{
    ASSERT(t == Type::String);
    return *s;
}

// =============================================================================
// (public)
const DateTime& CRef::getDateTime() const
{
    ASSERT(t == Type::DateTime);
    return *dt;
}

// =============================================================================
// (public)
bool CRef::canGet(Ref& target, bool allowConversion, Convert::Settings* settings) const
{
    if (t == Type::Undefined) { return false; }
    if (!allowConversion && target.t != t) { return false; }

    switch (target.t) {
    case Type::Undefined:
        return false;
    case Type::Char:
        return false;
    case Type::Bool:
        return canGet(*const_cast<bool*>(target.b), allowConversion, settings);
    case Type::Integer:
        return canGet(*const_cast<int*>(target.i), allowConversion, settings);
    case Type::Double:
        return canGet(*const_cast<double*>(target.d), allowConversion, settings);
    case Type::String:
        return canGet(*const_cast<std::string*>(target.s), allowConversion, settings);
    case Type::DateTime:
        return canGet(*const_cast<DateTime*>(target.dt), allowConversion, settings);
    default:
        ASSERT(false);
        return false;
    }
}

// =============================================================================
// (public)
bool CRef::get(Ref& target, bool allowConversion, Convert::Settings* settings) const
{
    if (t == Type::Undefined) { return false; }
    if (!allowConversion && target.t != t) { return false; }

    switch (target.t) {
    case Type::Undefined:
        return false;
    case Type::Char:
        return false;
    case Type::Bool:
        return get(*const_cast<bool*>(target.b), allowConversion, settings);
    case Type::Integer:
        return get(*const_cast<int*>(target.i), allowConversion, settings);
    case Type::Double:
        return get(*const_cast<double*>(target.d), allowConversion, settings);
    case Type::String:
        return get(*const_cast<std::string*>(target.s), allowConversion, settings);
    case Type::DateTime:
        return get(*const_cast<DateTime*>(target.dt), allowConversion, settings);
    default:
        ASSERT(false);
        return false;
    }
}

// =============================================================================
// (public)
bool CRef::canGet(Val& target, bool allowConversion, Convert::Settings* settings) const
{
    return canGet(dynamic_cast<Ref&>(target), allowConversion, settings);
}

// =============================================================================
// (public)
bool CRef::get(Val& target, bool allowConversion, Convert::Settings* settings) const
{
    return get(dynamic_cast<Ref&>(target), allowConversion, settings);
}

} // namespace VLS::Variant

