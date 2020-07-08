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

namespace VLS::Event {

/// <summary>
/// A threadsafe queue
/// The thread-safe queue is used by the async Event::HandlerAsync to transfer
/// event arguments from the trigger thread to a seperate worker thread
/// </summary>
template <class T>
class SafeQueue
{
public:

    /// <summary>
    /// 
    /// </summary>
    SafeQueue() = default;

    /// <summary>
    /// 
    /// </summary>
    SafeQueue(const SafeQueue&) = delete;

    /// <summary>
    /// Add a element to the queue
    /// </summary>
    /// <param name="value"> Queue element </param>
    void Enqueue(T value)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push(value);
        m_conVar.notify_one();
    }

    /// <summary>
    /// Get the front element of the queue. Wait if the queue is empty.
    /// </summary>
    /// <returns> Front element of the queue </returns>
    T Dequeue()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        while (m_queue.empty())
        {
            // release lock as long as the wait and reaquire it afterwards.
            m_conVar.wait(lock);
        }
        T value = m_queue.front();
        m_queue.pop();
        return value;
    }

private:
    /// <summary>
    /// 
    /// </summary>
    std::queue<T> m_queue;

    /// <summary>
    /// 
    /// </summary>
    std::mutex m_mutex;

    /// <summary>
    /// 
    /// </summary>
    std::condition_variable m_conVar;
};

}
