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

#include <VLS/Concurrent/IAsyncQueue.h>
#include <VLS/Concurrent/SafeQueue.h>

#include <atomic>
#include <functional>
#include <map>
#include <string>
#include <thread>

namespace VLS::Concurrent {

class AsyncQueue : public IAsyncQueue {
 public:
  AsyncQueue(const std::string& name);

  ~AsyncQueue() override;

  void exec(const std::function<void(void)>& func) override;

  void wait() override;

  bool sameThread() const override;

  const std::string& name() const override;

  static const std::string& threadName();

 private:
  void run();

  std::thread m_thread;

  SafeQueue<std::function<void(void)>> m_safeQueue;

  std::atomic<bool> m_run = true;

  std::string m_name;

  static std::map<std::thread::id, std::string> s_threadNameMap;
  static std::string s_defaultThreadName;
  static std::mutex s_threadNameMutex;
};

}  // namespace VLS::Concurrent
