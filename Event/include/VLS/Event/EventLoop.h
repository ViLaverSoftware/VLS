/*
 * Copyright 2020 Vilaversoftware IVS (http://vilaversoftware.dk/)
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

#include "VLS/Event/IEventLoop.h"
#include "VLS/Event/SafeQueue.h"

#include <functional>
#include <thread>
#include <atomic>
#include <string>
#include <map>

namespace VLS::Event {

/// <summary>
/// 
/// </summary>
class EventLoop : public IEventLoop
{
public:
    /// <summary>
    /// 
    /// </summary>
    EventLoop() = default;

    /// <summary>
    /// 
    /// </summary>
    ~EventLoop();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="">  </param>
    void Enqueue(const std::function<void(void)>& func) override;

    /// <summary>
    /// 
    /// </summary>
    /// <param name="">  </param>
    /// <return>  </return>
    bool Start(const std::string& name = std::string());
    bool Stop();

    /// <summary>
    /// 
    /// </summary>
    /// <return>  </return>
    static const std::string& ThreadName();

private:
    /// <summary>
    /// 
    /// </summary>
    void _run();

    /// <summary>
    /// 
    /// </summary>
    std::thread m_thread;

    /// <summary>
    /// 
    /// </summary>
    SafeQueue<std::function<void(void)>> m_eventQueue;

    /// <summary>
    /// 
    /// </summary>
    std::atomic_bool m_run = false;

    /// <summary>
    /// 
    /// </summary>
    static std::map<std::thread::id, std::string> s_threadNameMap;

    /// <summary>
    /// 
    /// </summary>
    static std::string s_defaultThreadName;
};

}
