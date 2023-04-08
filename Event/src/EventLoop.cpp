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
#include "VLS/Event/EventLoop.h"

namespace VLS::Event {

std::map<std::thread::id, std::string> EventLoop::s_threadNameMap;
std::string EventLoop::s_defaultThreadName = "Noname";
std::mutex EventLoop::s_threadNameMutex;

EventLoop::EventLoop() : m_run(false) {}

EventLoop::~EventLoop() { Stop(); }

void EventLoop::Enqueue(const std::function<void(void)>& func) {
  m_eventQueue.Enqueue(func);
}

bool EventLoop::Start(const std::string& name) {
  if (m_run) {
    return false;
  }
  m_run = true;
  m_thread = std::thread(&EventLoop::_run, this);

  // Add thread name to map
  if (!name.empty()) {
    s_threadNameMutex.lock();
    s_threadNameMap[m_thread.get_id()] = name;
    s_threadNameMutex.unlock();
  }
  return true;
}

bool EventLoop::Stop() {
  if (!m_run) {
    return false;
  }
  auto threadId = m_thread.get_id();
  m_run = false;

  // Wake up thread
  m_eventQueue.Enqueue([]() {});

  if (m_thread.joinable()) {
    m_thread.join();
  }

  // Remove thread name from map
  s_threadNameMutex.lock();
  auto it = s_threadNameMap.find(threadId);
  if (it != s_threadNameMap.end()) {
    s_threadNameMap.erase(it);
  }
  s_threadNameMutex.unlock();

  return true;
}

bool EventLoop::IsRunning() const { return m_run; }

size_t EventLoop::WaitingCount() const { return m_eventQueue.WaitingCount(); }

const std::string& EventLoop::ThreadName() {
  std::lock_guard<std::mutex> guard(s_threadNameMutex);
  auto it = s_threadNameMap.find(std::this_thread::get_id());
  if (it != s_threadNameMap.end()) {
    return it->second;
  }
  return s_defaultThreadName;
}

void EventLoop::_run() {
  do {
    auto func = m_eventQueue.Dequeue();
    func();
  } while (m_run);
}

}  // namespace VLS::Event
