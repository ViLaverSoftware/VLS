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

#include <functional>

namespace VLS::Event {

/// <summary>
/// Interface class for the EventLoop class.
/// </summary>
/// <remarks>
/// By having an interface it is possible to create an alternative
/// implementation of the EventLoop class. The interface contains the only
/// function used by the EventHandler class.
/// </remarks>
class IEventLoop {
 public:
  virtual ~IEventLoop() = default;

  /// <summary>
  /// Function is triggered when the EventHandler Trigger() function is called.
  /// </summary>
  /// <remarks>
  /// The triggered function is packed into a lambda function with no arguments
  /// or return value, but the arguments of the triggered event is included in
  /// the lambda function and used when the func is called.
  /// </remarks>
  /// <param name=""> Callable function with no arguments or return value.
  /// </param>
  virtual void Enqueue(const std::function<void(void)>& func) = 0;
};

}  // namespace VLS::Event
