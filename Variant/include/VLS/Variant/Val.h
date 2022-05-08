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

#pragma once

#include "VLS/Variant/Ref.h"

namespace VLS::Variant {

class Val : public Ref
{
public:
    Val();
    Val(const char* _c);
    Val(const bool& _b);
    Val(const int& _i);
    Val(const double& _d);
    Val(const std::string& _s);
    Val(const DateTime& _dt);
    Val(const CRef& value);

    ~Val() override;
};

}
