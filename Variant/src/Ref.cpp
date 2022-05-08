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

#include "VLS/Variant/Ref.h"


namespace VLS::Variant {

// =============================================================================
// (public)
Ref::Ref()
    : CRef()
{
}

// =============================================================================
// (public)
Ref::Ref(bool& _b)
    : CRef(_b)
{
}

// =============================================================================
// (public)
Ref::Ref(int& _i)
    : CRef(_i)
{
}

// =============================================================================
// (public)
Ref::Ref(double& _d)
    : CRef(_d)
{
}

// =============================================================================
// (public)
Ref::Ref(std::string& _s)
    : CRef(_s)
{
}

// =============================================================================
// (public)
Ref::Ref(DateTime& _dt)
    : CRef(_dt)
{
}

// =============================================================================
// (public)
Ref::Ref(Ref& copy)
    : CRef(copy)
{
}

// =============================================================================
// (public)
Ref& Ref::operator=(const CRef& copy)
{
    bool result = copy.get(*this);
    ASSERT(result);
    return *this;
}

}
