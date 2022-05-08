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

#include "VLS/Variant/CRef.h"

namespace VLS::Variant {

class Ref : public CRef
{
public:
    Ref();
    Ref(bool& _b);
    Ref(int& _i);
    Ref(double& _d);
    Ref(std::string& _s);
    Ref(DateTime& _dt);
    Ref(Ref& copy);

    Ref& operator=(const CRef& copy);

    template<typename T>
    Ref& operator=(T value) { return *this = CRef(value); }
    
};

}
