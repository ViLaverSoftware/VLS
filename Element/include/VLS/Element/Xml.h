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

#include "VLS/Element/Abstract.h"

#include "pugixml.hpp"
#include <tuple>

namespace VLS::Element {

// =============================================================================
// Class definition
// =============================================================================
class XML: public Abstract
{

    enum class ValueType {
        Attribute,
        Element,
        Text
    };

public:
    XML();

    std::string Name() const override;
    VLS::Element::Type Type() const override;

    bool IsNull() const override;
    bool Empty() const override;
    
    bool ToParent() override;

    bool ChildCount(const std::string& name) override;

    bool ToFirstChild(const std::string& name) override;
    bool ToNextSibling(const std::string& name) override;

    bool ToLastChild(const std::string& name) override;
    bool ToPreviousSibling(const std::string& name) override;


    bool HasValue(const std::string& valueName = std::string()) override;
    bool GetValue(VLS::Variant::Ref& value, const std::string& valueName = std::string()) override;
    bool SetValue(const VLS::Variant::Ref& value, const std::string& valueName = std::string()) override;
    int CompareValue(const VLS::Variant::Ref& value, const std::string& valueName = std::string()) override;

    static std::tuple<ValueType, const char*> ParseValueName(const std::string& valueName);
    static ValueType DefaultValueType();
    static void SetDefaultValueType(ValueType vType);

private:
    const char* ValueCPtr(const std::string& valueName) const;

protected:
    pugi::xml_node m_element;
    static ValueType s_defaultValueType;
};

} // namespace XML::Element
