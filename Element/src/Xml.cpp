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

#include "VLS/Element/XML.h"

#include "VLS/Utilities/Assert.h"

namespace VLS::Element {

XML::ValueType XML::s_defaultValueType = XML::ValueType::Element;

// =============================================================================
//
XML::XML()
	: Abstract()
{

}

// =============================================================================
//
std::string XML::Name() const
{
    return std::string(m_element.name());
}

Type XML::Type() const
{
	return VLS::Element::Type::XML;
}

// =============================================================================
//
bool XML::IsNull() const
{
    return m_element.empty() || *m_element.name() == 0;
}

// =============================================================================
//
bool XML::Empty() const
{
    if (m_element.empty()) {
        // Null element
        return true;
    }
    if (*m_element.value() != 0) {
        // Element has text
        return false;
    }
    if (m_element.begin() != m_element.end()) {
        // Element has child element
        return false;
    }
    if (m_element.attributes_begin() != m_element.attributes_end()) {
        // Element has an attribute
        return false;
    }
    // Element exists but is empty
    return true;
}

// =============================================================================
//
bool XML::ToParent()
{
    m_element = m_element.parent();
    return !m_element.empty();
}

// =============================================================================
//
bool XML::ChildCount(const std::string& name)
{
    int count = 0;
    XML element(*this);
    element.ToFirstChild(name);
    while (!element.IsNull()) {
        count++;
        element.ToNextSibling(name);
    }
    return count;
}

// =============================================================================
//
bool XML::ToFirstChild(const std::string& name)
{
    pugi::xml_node node = m_element.first_child();
    while (!node.empty()) {
        if (node.type() == pugi::node_element) {
            if (name.empty() || name.compare(node.name()) == 0) {
                m_element = node;
                return true;
            }
        }
        node = node.next_sibling();
    }
    m_element = node;
    return false;
}

// =============================================================================
//
bool XML::ToNextSibling(const std::string& name)
{
    pugi::xml_node node = m_element.next_sibling();
    while (!node.empty()) {
        if (node.type() == pugi::node_element) {
            if (name.empty() || name.compare(node.name()) == 0) {
                m_element = node;
                return true;
            }
        }
        node = node.next_sibling();
    }
    m_element = node;
    return false;
}

// =============================================================================
//
bool XML::ToLastChild(const std::string& name)
{
    pugi::xml_node node = m_element.last_child();
    while (!node.empty()) {
        if (node.type() == pugi::node_element) {
            if (name.empty() || name.compare(node.name()) == 0) {
                m_element = node;
                return true;
            }
        }
        node = node.previous_sibling();
    }
    m_element = node;
    return false;
}

// =============================================================================
//
bool XML::ToPreviousSibling(const std::string& name)
{
    pugi::xml_node node = m_element.previous_sibling();
    while (!node.empty()) {
        if (node.type() == pugi::node_element) {
            if (name.empty() || name.compare(node.name()) == 0) {
                m_element = node;
                return true;
            }
        }
        node = node.previous_sibling();
    }
    m_element = node;
    return false;
}

// =============================================================================
//
bool XML::HasValue(const std::string& valueName)
{
    // Empty value strings are considered the same as no value
    const char* valuePtr = ValueCPtr(valueName);
    if (valuePtr == nullptr || valuePtr[0] == '\0') { return false; }
    return true;
}

// =============================================================================
//
bool XML::GetValue(VLS::Variant::Ref& value, const std::string& valueName)
{
    const char* valuePtr = ValueCPtr(valueName);
    if (valuePtr == nullptr || valuePtr[0] == '\0') {
        //value.Clear();
        return false; 
    }
    //value = valuePtr;
    return true;
}

// =============================================================================
//
bool XML::SetValue(const VLS::Variant::Ref& value, const std::string& valueName)
{
    return false;
}

// =============================================================================
//
int XML::CompareValue(const VLS::Variant::Ref& value, const std::string& valueName)
{
    return 0;
}

// =============================================================================
// Static
std::tuple<XML::ValueType, const char*> XML::ParseValueName(const std::string& valueName)
{
    if (valueName.empty()) {
        return { XML::ValueType::Text, nullptr };
    } else if (valueName.size() > 1 && valueName[1] == ':') {
        if (valueName[0] == 'A' || valueName[0] == 'a') {
            return { XML::ValueType::Attribute, valueName.c_str() + 2 };
        } if (valueName[0] == 'E' || valueName[0] == 'e') {
            return { XML::ValueType::Element, valueName.c_str() + 2 };
        }
        // Unknown Value type identifier
        ASSERT(false);
    }
    
    return { DefaultValueType(), valueName.c_str() };
}

// =============================================================================
// Static
XML::ValueType XML::DefaultValueType()
{
    return s_defaultValueType;
}

// =============================================================================
// Static
void XML::SetDefaultValueType(XML::ValueType vType)
{
    s_defaultValueType = vType;
}

// =============================================================================
// Private
const char* XML::ValueCPtr(const std::string& valueName) const
{
    auto [vType, cPtr] = ParseValueName(valueName);

    switch (vType) {
    case ValueType::Text:
        return m_element.text().empty() ? nullptr : m_element.text().get();
        break;
    case ValueType::Element: {
        pugi::xml_node cElement = m_element.first_child();
        while (!cElement.empty()) {
            if (cElement.type() == pugi::node_element) {
                if (std::strcmp(cPtr, cElement.name()) == 0) {
                    return cElement.text().empty() ? nullptr : cElement.text().get();
                }
            }
            cElement = cElement.next_sibling();
        }
        break;
    }
    case ValueType::Attribute: {
        auto it = m_element.attributes_begin();
        auto itEnd = m_element.attributes_end();
        while (it != itEnd) {
            if (std::strcmp(cPtr, it->name()) == 0) {
                return it->value();
            }
            it++;
        }
        break;
    }
    default:
        ASSERT(false);
    }

    return nullptr;
}

} // namespace XML::Element
