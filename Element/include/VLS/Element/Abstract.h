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

namespace VLS::Variant {
class Ref;
class Value;
};

namespace VLS::Element {

enum class Type {
    XML,
    JSON,
    Memory
};


// =============================================================================
// Class definition
// =============================================================================
class Abstract
{
public:
    Abstract();
    virtual ~Abstract() = default;

    virtual std::string Name() const = 0;
    virtual Type Type() const = 0;

    virtual bool IsNull() const = 0;
    virtual bool Empty() const = 0;

    virtual bool ToParent() = 0;

    virtual bool ChildCount(const std::string& name = std::string()) = 0;

    virtual bool ToFirstChild(const std::string& name = std::string()) = 0;
    virtual bool ToNextSibling(const std::string& name = std::string()) = 0;

    virtual bool ToLastChild(const std::string& name = std::string()) = 0;
    virtual bool ToPreviousSibling(const std::string& name = std::string()) = 0;


    virtual bool HasValue(const std::string& valueName = std::string()) = 0;
    virtual bool GetValue(VLS::Variant::Ref& value, const std::string& valueName = std::string()) = 0;
    virtual bool SetValue(const VLS::Variant::Ref& value, const std::string& valueName = std::string()) = 0;
    virtual int CompareValue(const VLS::Variant::Ref& value, const std::string& valueName = std::string()) = 0;

protected:

};

} // namespace VLS::Element
