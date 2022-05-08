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

#include <string>

#include "VLS/DateTime.h"

namespace VLS::Variant {

class Reference;
class Value;

enum class Type { 
    Undefined = -1,
    Char = 0,
    Bool = 1,
    Integer = 2,
    Double = 3,
    String = 4,
    DateTime = 5
};

union ValueUnion {
    bool b;
    int i;
    double d;
    std::string *s;
    DateTime *dt;
    ValueUnion() {
        memset(this, 0, sizeof(ValueUnion));
    }
};

union PointerUnion {
    const char *c;
    const bool *b;
    const int *i;
    const double *d;
    const std::string *s;
    const DateTime *dt;
    PointerUnion() {
        memset(this, 0, sizeof(PointerUnion));
    }
};

Type GetType(type_info info);
Type GetType(const char*);
Type GetType(bool);
Type GetType(int);
Type GetType(double);
Type GetType(const std::string&);
Type GetType(const DateTime&);
Type GetType(Type t);
Type GetType(const Reference& ur);
Type GetType(const Value& uv);

// =============================================================================
// (public)
template<typename T>
Type GetValueType(const T &v)
{
    Type type = GetType(v);
    return (type == Type::Char) ? Type::String : type;

}

} // namespace VLS::Variant

