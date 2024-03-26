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

#include <mutex>
#include <queue>

namespace VLS::Concurrent {
/**
 * @brief The SafeQueue class implements a thread safe queue.
 */
template <class T>
class SafeQueue {
 public:
  SafeQueue() = default;
  SafeQueue(const SafeQueue&) = delete;

  /**
   * @brief enqueue adds an element to the queue.
   * @param value the element that is added to the queue.
   */
  void enqueue(T value) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_queue.push(value);
    m_conVar.notify_one();
  }

  /**
   * @brief dequeue gets the front element of the queue. Wait if the queue is
   * empty.
   * @return the first element in the queue.
   */
  T dequeue() {
    std::unique_lock<std::mutex> lock(m_mutex);
    while (m_queue.empty()) {
      // release lock as long as the wait and reacquire it afterwards.
      m_conVar.wait(lock);
    }
    T value = m_queue.front();
    m_queue.pop();
    return value;
  }

 private:
  std::queue<T> m_queue;
  std::mutex m_mutex;
  std::condition_variable m_conVar;
};

}  // namespace VLS::Concurrent
