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

#include <atomic>
#include <functional>
#include <map>
#include <string>
#include <thread>

#include "VLS/Event/IEventLoop.h"
#include "VLS/Event/SafeQueue.h"

namespace VLS::Event {

/// <summary> Continuously executes functions on a thread when running.
/// </summary> <remarks> Thread is not started when object is created. When the
/// thread is running functions are executed in the order they are enqueued.
/// When there are no functions to execute the thread waits. Thread name can be
/// added when thread is started and the static function ThreadName() can be
/// used to access the name of the current thread.
/// </remarks>
class EventLoop : public IEventLoop {
 public:
  /// <summary>
  /// Constructor do not start the event loop.
  /// </summary>
  EventLoop();

  /// <summary>
  /// Destructor stops the event loop if it is running and waits for it to end
  /// before returning.
  /// </summary>
  ~EventLoop();

  /// <summary>
  /// Adds the callable to the event loop function queue.
  /// </summary>
  /// <remarks>
  /// It will be called when the thread is running and all callables added
  /// before it has returned.
  /// </remarks>
  /// <param name=""> Callable function with no arguments or return value.
  /// </param>
  void Enqueue(const std::function<void(void)>& func) override;

  /// <summary>
  /// Starts the thread.
  /// </summary>
  /// <remarks>
  /// If a name is provided it is added to a map of thread id/names.
  /// Thread name can be accesses with the static function ThreadName().
  /// </remarks>
  /// <param name=""> Optional thread name. </param>
  /// <returns> True if the thread is started. </returns>
  bool Start(const std::string& name = std::string());

  /// <summary>
  /// Stops the thread if it is running.
  /// </summary>
  /// <remarks>
  /// Waits for the thread to end before returning.
  /// </remarks>
  /// <returns> Returns true if the thread has been stopped. </returns>
  bool Stop();

  /// <summary>
  /// Returns if the thread is currently running.
  /// </summary>
  /// <returns> True if the thread is running. </returns>
  bool IsRunning() const;

  /// <summary>
  /// Returns the number of callable functions that haven't been called yet.
  /// </summary>
  /// <returns> Number of waiting callable functions. </returns>
  size_t WaitingCount() const;

  /// <summary>
  /// Return the name of the current thread if it has a name otherwise return
  /// the default name.
  /// </summary>
  /// <returns> Name of the current thread. </returns>
  static const std::string& ThreadName();

 private:
  /// <summary>
  /// Internal main function of the thread.
  /// </summary>
  void _run();

  /// <summary>
  /// Thread
  /// </summary>
  std::thread m_thread;

  /// <summary>
  /// Que with all the callables that haven't been triggered yet.
  /// </summary>
  SafeQueue<std::function<void(void)>> m_eventQueue;

  /// <summary>
  /// Set to true when the thread is started and false when it should be stopped
  /// after the next callable returns or immediately if waiting.
  /// </summary>
  std::atomic<bool> m_run;

  /// <summary>
  /// Map with thread id/names
  /// </summary>
  static std::map<std::thread::id, std::string> s_threadNameMap;

  /// <summary>
  /// Name returned when thread to no exists in the thread name map.
  /// </summary>
  static std::string s_defaultThreadName;

  /// <summary>
  /// Mutex for the thread name map
  /// </summary>
  static std::mutex s_threadNameMutex;
};

}  // namespace VLS::Event
