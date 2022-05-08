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

#include "VLS/Variant/Val.h"

#include "VLS/Utilities/Assert.h"

namespace VLS::Variant {

Val::Val()
    : Ref()
{

}

Val::Val(const char* _c)
    : Ref()
{
    t = Type::String;
    s = new std::string(_c);
}

Val::Val(const bool& _b)
    : Ref(const_cast<bool&>(_b))
{
    b = new bool(_b);
}

Val::Val(const int& _i)
    : Ref(const_cast<int&>(_i))
{
    i = new int(_i);
}

Val::Val(const double& _d)
    : Ref(const_cast<double&>(_d))
{
    d = new double(_d);
}

Val::Val(const std::string& _s)
    : Ref(const_cast<std::string&>(_s))
{
    s = new std::string(_s);
}

Val::Val(const DateTime& _dt)
    : Ref(const_cast<DateTime&>(_dt))
{
    dt = new DateTime(_dt);
}

Val::Val(const CRef& value)
    : Ref()
{
    t = value.type();
    switch (t) {
    case Type::Undefined:
        i = nullptr;
        break;
    case Type::Char:
        t = Type::String;
        s = new std::string(value.getCString());
        break;
    case Type::Bool:
        b = new bool(value.getBool());
        break;
    case Type::Integer:
        i = new int(value.getInt());
        break;
    case Type::Double:
        d = new double(value.getDouble());
        break;
    case Type::String:
        s = new std::string(value.getString());
        break;
    case Type::DateTime:
        dt = new DateTime(value.getDateTime());
        break;
    default:
        ASSERT(false);
    }
}

Val::~Val()
{
    switch (t) {
    case Type::Undefined:
        break;
    case Type::Char:
        delete[] c;
        break;
    case Type::Bool:
        delete b;
        break;
    case Type::Integer:
        delete i;
        break;
    case Type::Double:
        delete d;
        break;
    case Type::String:
        delete s;
        break;
    case Type::DateTime:
        delete dt;
        break;
    default:
        ASSERT(false);
    }
}

}