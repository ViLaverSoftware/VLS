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

#include "VLS/Convert/Settings.h"


namespace VLS::Convert {

// =============================================================================
// (public)
Settings::Settings()
{
}

// =============================================================================
// (public)
SettingsSPtr Settings::globalDefaultSPtr()
{
    static SettingsSPtr globalDefault(globalDefault());

    return globalDefault;
}

// =============================================================================
// (public)
Settings* Settings::globalDefault()
{
    static Settings* s_default = new Settings();

    // Initialize the global default conversion
    if (s_default->m_boolTrue.empty()) {
        s_default->m_boolTrue = "true";
        s_default->m_boolFalse = "false";
        s_default->m_listSeperator = ";";
        s_default->m_roundRules = DoubleToInt::Round;
        s_default->m_equalTolerance = 1.0e-12;
        s_default->m_doubleToStringPrecision = 5;
        s_default->m_doubleToStringMode = DoubleToString::Default;
    }

    return s_default;
}

} // namespace VLS::Convert

