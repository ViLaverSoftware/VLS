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

#include "VLS/Variant/Base.h"

#include "VLS/Variant/Reference.h"
#include "VLS/Variant/Value.h"


namespace VLS::Variant {

// =============================================================================
// (public)
Type GetType(type_info info)
{
    if (typeid(std::string) == info) {
        return Type::String;
    }
    if (typeid(double) == info) {
        return Type::Double;
    }
    if (typeid(int) == info) {
        return Type::Integer;
    }
    if (typeid(bool) == info) {
        return Type::Bool;
    }
    if (typeid(char) == info) {
        return Type::Char;
    }
    if (typeid(DateTime) == info) {
        return Type::DateTime;
    }
    return Type::Undefined;
}

// =============================================================================
// (public)
Type GetType(const char *)
{
    return Type::Char;
}

// =============================================================================
// (public)
Type GetType(bool)
{
    return Type::Bool;
}

// =============================================================================
// (public)
Type GetType(int)
{
    return Type::Integer;
}

// =============================================================================
// (public)
Type GetType(double)
{
    return Type::Double;
}

// =============================================================================
// (public)
Type GetType(const std::string &)
{
    return Type::String;
}

// =============================================================================
// (public)
Type GetType(const DateTime &)
{
    return Type::DateTime;
}

// =============================================================================
// (public)
Type GetType(Type t)
{
    return t;
}

// =============================================================================
// (public)
Type GetType(const Reference &ur)
{
    return ur.type();
}

// =============================================================================
// (public)
Type GetType(const Value &uv)
{
    return uv.type();
}

} // namespace VLS::Variant

