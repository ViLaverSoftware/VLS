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

#include "Assert.h"

#ifdef WIN32

#include <Windows.h>
#include <stdio.h>

struct Tracer
{
    char const * m_fileName;
    unsigned m_line;

    Tracer(const char * fileName, const unsigned line)
        : m_fileName { fileName },
          m_line { line }
    {
    }

    template <typename... Args>
    void operator() (const wchar_t * format, Args... args) const
    {
        if (blocked()) { return; }
        wchar_t buffer [256];

        auto count = swprintf_s(buffer,
                                L"%S(%d): ",
                                m_fileName,
                                m_line);

        ASSERT(-1 != count);

        ASSERT(-1 != _snwprintf_s(buffer + count,
                                  _countof(buffer) - count,
                                  _countof(buffer) - count - 1,
                                  format,
                                  args...));

        OutputDebugStringW(buffer);
    }

    template <typename... Args>
    void operator() (const char * format, Args... args) const
    {
        if (blocked()) { return; }
        char buffer [256];

        auto count = sprintf_s(buffer,
                               "%s(%d): ",
                               m_fileName,
                               m_line);

        ASSERT(-1 != count);

        ASSERT(-1 != _snprintf_s(buffer + count,
                                 _countof(buffer) - count,
                                 _countof(buffer) - count - 1,
                                 format,
                                 args...));

        OutputDebugStringA(buffer);
    }

    static bool &blocked()
    {
        static bool blocked = false;
        return blocked;
    }
};



#else
// Todo: Implement linux/mac tracer function here!
#endif

#ifdef _DEBUG
#ifdef WIN32
#define TRACE Tracer(__FILE__, __LINE__)
#define TRACE_BLOCK Tracer::blocked()
#else
// Todo: Implement linux/mac TRACE macro here!
#define TRACE __noop
#define TRACE_BLOCK __noop
#endif
#else
#define TRACE __noop
#define TRACE_BLOCK __noop
#endif
