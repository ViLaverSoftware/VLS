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
#include <VLS/Concurrent/AsyncQueue.h>
#include <VLS/Log/Log.h>

#include <format>
#include <latch>

namespace VLS::Concurrent {

std::map<std::thread::id, std::string> AsyncQueue::s_threadNameMap;
std::string AsyncQueue::s_defaultThreadName = "Noname";
std::mutex AsyncQueue::s_threadNameMutex;

AsyncQueue::AsyncQueue(const std::string& name) : m_name{name} {
  m_thread = std::thread(&AsyncQueue::run, this);

  logInfo(std::format("Created thread for async queue {}", m_name));

  // Add thread name to map
  if (!m_name.empty()) {
    std::lock_guard<std::mutex> lock(s_threadNameMutex);
    s_threadNameMap[m_thread.get_id()] = m_name;
  }
}

AsyncQueue::~AsyncQueue() {
  auto threadId = m_thread.get_id();

  logInfo(std::format("Destructing async queue {}", m_name));
  // Finish up everything already on the queue
  wait();
  exec([this]() { m_run = false; });

  m_thread.join();
  logInfo(std::format("Thread of async queue {} is now joined", m_name));

  // Remove thread name from map
  std::lock_guard<std::mutex> lock(s_threadNameMutex);
  auto it = s_threadNameMap.find(threadId);
  if (it != s_threadNameMap.end()) {
    s_threadNameMap.erase(it);
  }
}

void AsyncQueue::exec(const std::function<void(void)>& func) {
  m_safeQueue.enqueue(func);
}

void AsyncQueue::wait() {
  std::latch latch{1};

  // Execute a function that will release the latch
  exec([&latch]() { latch.count_down(); });
  latch.wait();
}

bool AsyncQueue::sameThread() const {
  return std::this_thread::get_id() == m_thread.get_id();
}

const std::string& AsyncQueue::name() const { return m_name; }

const std::string& AsyncQueue::threadName() {
  std::lock_guard<std::mutex> lock(s_threadNameMutex);
  auto it = s_threadNameMap.find(std::this_thread::get_id());
  if (it != s_threadNameMap.end()) {
    return it->second;
  }
  return s_defaultThreadName;
}

void AsyncQueue::run() {
  do {
    try {
      auto func = m_safeQueue.dequeue();
      func();
    } catch (...) {
      logError(std::format("Exception while async queue {} is executing a job.",
                           m_name));
    }

  } while (m_run);
}

}  // namespace VLS::Concurrent
