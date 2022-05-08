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
#include <chrono>


namespace VLS {

// =============================================================================
// Struct definition
// =============================================================================
struct ProcessedDateTime {
    int year;
    int month;
    int day;

    int hour;
    int minute;
    int secound;

    ProcessedDateTime & operator-=(const ProcessedDateTime &other)
    {
        year -= other.year;
        month -= other.month;
        day -= other.day;

        hour -= other.hour;
        minute -= other.minute;
        secound -= other.secound;
        return *this;
    }

    bool isNull() const
    {
        return year == 0 &&
               month == 0 &&
               day == 0 &&
               hour == 0 &&
               minute == 0 &&
               secound == 0;
    }
};

// =============================================================================
// Class definition
// =============================================================================
class DateTime
{
public:

    enum class TimeZone {
        UTC = 0,
        Local = 1
    };

    DateTime();
    DateTime(int year, int month, int day, int hour = 0, int minute = 0, int secound = 0, TimeZone timeZone = TimeZone::Local);
    DateTime(const std::string &str, TimeZone timeZone = TimeZone::Local, const char *format = "%Y-%m-%d %H:%M:%S");

    DateTime(const DateTime &copy) noexcept;
    DateTime(DateTime &&move) noexcept;

    DateTime &operator=(const DateTime &copy);
    DateTime &operator=(DateTime &&move) noexcept;

    bool operator==(const DateTime &other) const;
    bool operator!=(const DateTime &other) const;

    bool operator<(const DateTime &other) const;

    bool isNull() const;

    static DateTime now();

    void swap(DateTime &other) noexcept;

    int year(DateTime::TimeZone timeZone = TimeZone::Local) const;
    int month(DateTime::TimeZone timeZone = TimeZone::Local) const;
    int day(TimeZone timeZone = TimeZone::Local) const;

    int hour(DateTime::TimeZone timeZone = TimeZone::Local) const;
    int minute() const;
    int secound() const;

    long long mSecsSinceEpoch() const;
    void setMSecsSinceEpoch(long long ms);

    ProcessedDateTime toStruct(TimeZone timeZone = TimeZone::Local) const;

    std::string toString(TimeZone timeZone = TimeZone::Local, const char *format = "%Y-%m-%d %H:%M:%S") const;
    std::string toString(const ProcessedDateTime & pdt) const;

    static const DateTime & emptyDateTime();
    static const DateTime & defaultDateTime();

protected:
    static int _monthDaySum(size_t month);
    static int _monthDays(size_t month);

    static const std::chrono::system_clock::time_point & _emptyTimePoint();

protected:
    std::chrono::system_clock::time_point m_time;
};

void swap(DateTime &left, DateTime &right) noexcept;

typedef std::chrono::duration<int, std::ratio_multiply<std::chrono::hours::period, std::ratio<24> >::type> chrono_days;

} // namespace VLS

