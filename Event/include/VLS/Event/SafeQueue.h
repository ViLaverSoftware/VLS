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
/// A thread safe queue.
/// <remarks>
/// The thread-safe queue is used by the async Event::HandlerAsync to transfer
/// callables from the trigger thread to a separate event loop thread.
/// </remarks>
/// </summary>
template <class T>
class SafeQueue
{
public:

    SafeQueue() = default;

    /// <summary>
    /// Queue can not be copied.
    /// </summary>
    SafeQueue(const SafeQueue&) = delete;

    /// <summary>
    /// Add a element to the queue.
    /// </summary>
    /// <param name="value"> Queue element. </param>
    void Enqueue(T value)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push(value);
        m_conVar.notify_one();
    }

    /// <summary>
    /// Get the front element of the queue. Wait if the queue is empty.
    /// </summary>
    /// <returns> Front element of the queue. </returns>
    T Dequeue()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        while (m_queue.empty())
        {
            // release lock as long as the wait and reacquire it afterwards.
            m_conVar.wait(lock);
        }
        T value = m_queue.front();
        m_queue.pop();
        return value;
    }

    /// <summary>
    /// Returns the number of elements on the queue.
    /// </summary>
    /// <returns> Number of elements on the queue. </returns>
    size_t WaitingCount() const 
    {
        return m_queue.size();
    }

private:
    /// <summary>
    /// Queue with elements.
    /// </summary>
    std::queue<T> m_queue;

    /// <summary>
    /// Mutex used to protect the queue.
    /// </summary>
    std::mutex m_mutex;

    /// <summary>
    ///  Used to wait for new elements.
    /// </summary>
    std::condition_variable m_conVar;
};

}
