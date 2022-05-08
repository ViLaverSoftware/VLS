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

#include "VLS/Convert/Functions.h"

#include "VLS/Utilities/Assert.h"

#include <iomanip>
#include <ctime>
#include <sstream>

namespace VLS::Convert {

// =============================================================================
// convert()
// =============================================================================

// =============================================================================
// (public)
bool convert(bool& dest, int src, Settings* )
{
    dest = src != 0;
    return true;
}

// =============================================================================
// (public)
bool convert(int& dest, bool src, Settings* )
{
    dest = src ? 1 : 0;
    return true;
}

// =============================================================================
// (public)
bool convert(bool&, double, Settings* )
{
    return false;
}

// =============================================================================
// (public)
bool convert(double&, bool, Settings* )
{
    return false;
}

// =============================================================================
// (public)
bool convert(bool& dest, const std::string& src, Settings* settings)
{
    if (settings == nullptr) { settings = Settings::globalDefault(); }
    if (src.compare(settings->boolTrue()) == 0) {
        dest = true;
        return true;
    } else if (src.compare(settings->boolFalse()) == 0) {
        dest = false;
        return true;
    }
    return false;
}

// =============================================================================
// (public)
bool convert(std::string& dest, bool src, Settings* settings)
{
    if (settings == nullptr) { settings = Settings::globalDefault(); }
    if (src) {
        dest = settings->boolTrue();
    } else {
        dest = settings->boolFalse();
    }
    return true;
}

// =============================================================================
// (public)
bool convert(int& dest, double src, Settings* settings)
{
    if (settings == nullptr) { settings = Settings::globalDefault(); }
    if (settings->roundRules() == Settings::DoubleToInt::Round) {
        dest = static_cast<int>(std::round(src));
    } else if (settings->roundRules() == Settings::DoubleToInt::Floor) {
        dest = static_cast<int>(std::floor(src));
    } else if (settings->roundRules() == Settings::DoubleToInt::Ceil) {
        dest = static_cast<int>(std::ceil(src));
    } else if (settings->roundRules() == Settings::DoubleToInt::Trunc) {
        dest = static_cast<int>(std::trunc(src));
    }
    return true;
}

// =============================================================================
// (public)
bool convert(double& dest, int src, Settings* )
{
    dest = src;
    return true;
}

// =============================================================================
// (public)
bool convert(int& dest, const std::string& src, Settings* )
{
    try {
        dest = std::stoi(src);
    } catch(...) {
        return false;
    }
    return true;
}

// =============================================================================
// (public)
bool convert(std::string& dest, int src, Settings* )
{
    dest = std::to_string(src);
    return true;
}

// =============================================================================
// (public)
bool convert(double& dest, const std::string& src, Settings* )
{
    try {
        dest = std::stod(src);
    } catch(...) {
        return false;
    }
    return true;
}

// =============================================================================
// (public)
bool convert(std::string& dest, double src, Settings* settings)
{
    if (settings == nullptr) { settings = Settings::globalDefault(); }
    std::stringstream stream;
    switch (settings->doubleToStringMode()) {
    case Settings::DoubleToString::Default:
        stream << std::defaultfloat;
        break;
    case Settings::DoubleToString::Scientific:
        stream << std::scientific;
        break;
    case Settings::DoubleToString::Fixed:
        stream << std::fixed;
        break;
    default:
        ASSERT(false);
        break;
    }
    stream << std::setprecision(settings->doubleToStringPrecision()) << src;
    dest = stream.str();
    return true;
}

// =============================================================================
// (public)
bool convert(std::string &dest, const char *source, Settings* )
{
    if (source == nullptr) { return false; }
    dest.assign(source);
    return true;
}

// =============================================================================
// (public)
bool convert(std::string &dest, const DateTime &src, Settings* settings)
{
    UNUSED(settings);
    if (src.isNull()) { return false; }
    dest = src.toString(DateTime::TimeZone::UTC, nullptr);
    return true;
}

// =============================================================================
// (public)
bool convert(DateTime &dest, const std::string &src, Settings* settings)
{
    UNUSED(settings);
    DateTime dt(src, DateTime::TimeZone::UTC);
    if (dt.isNull()) { return false; }
    dest = dt;
    return true;
}

// =============================================================================
// canConvert()
// =============================================================================

// =============================================================================
// (public)
bool canConvert(bool&, int&, Settings*)
{
    return true;
}

// =============================================================================
// (public)
bool canConvert(int&, const bool&, Settings*)
{
    return true;
}

// =============================================================================
// (public)
bool canConvert(bool &, double, Settings*)
{
    return false;
}

// =============================================================================
// (public)
bool canConvert(double&, bool, Settings*)
{
    return false;
}

// =============================================================================
// (public)
bool canConvert(std::string&, bool, Settings*)
{
    return true;
}

// =============================================================================
// (public)
bool canConvert(int&, double, Settings*)
{
    return true;
}

// =============================================================================
// (public)
bool canConvert(double&, int, Settings*)
{
    return true;
}

// =============================================================================
// (public)
bool canConvert(std::string&, const int&, Settings*)
{
    return true;
}

// =============================================================================
// (public)
bool canConvert(std::string&, const double&, Settings*)
{
    return true;
}

// =============================================================================
// (public)
bool canConvert(std::string &, const char *source, Settings*)
{
    return source != nullptr;
}

// =============================================================================
// (public)
bool canConvert(std::string &, const DateTime &src, Settings*)
{
    return !src.isNull();
}

// =============================================================================
// (public)
bool canConvert(DateTime &, const std::string &src, Settings*)
{
    return !DateTime(src, DateTime::TimeZone::UTC).isNull();
}

} // namespace VLS::Convert

