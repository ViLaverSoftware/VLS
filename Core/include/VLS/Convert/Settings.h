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
#include <memory>
#include <vector>

#ifndef UNUSED
#define UNUSED(x) (void)x;
#endif


namespace VLS::Convert {

class Settings;
using SettingsSPtr = std::shared_ptr<Settings>;

// =============================================================================
// Class definition
// =============================================================================
class Settings
{
public:
    enum class DoubleToInt {
        Round = 0,
        Floor,
        Ceil,
        Trunc
    };

    enum class DoubleToString {
        Default = 0,
        Fixed,
        Scientific
    };

public:
    Settings();

    const std::string &boolTrue() const { return m_boolTrue; }
    const std::string &boolFalse() const { return m_boolFalse; }

    double equalTolerance() const { return m_equalTolerance; }

    static SettingsSPtr globalDefaultSPtr();
    static Settings* globalDefault();

    DoubleToInt roundRules() const { return m_roundRules; }

    int doubleToStringPrecision() const { return m_doubleToStringPrecision; }
    DoubleToString doubleToStringMode() const { return m_doubleToStringMode; }
private:
    // Bool to string and back
    std::string m_boolTrue;
    std::string m_boolFalse;

    int m_doubleToStringPrecision = 5;
    DoubleToString m_doubleToStringMode = DoubleToString::Default;

    // Double to integer
    DoubleToInt m_roundRules = DoubleToInt::Round;

    //ToDo: Double to string rules

    std::string m_listSeperator;

    double m_equalTolerance = 1.0e-12;
};

} // namespace VLS::Convert

