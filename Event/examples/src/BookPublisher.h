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

#include "IBookPublisher.h"
#include "VLS/Event/EventHandler.h"

class BookPublisher : public IBookPublisher {
 public:
  void AddBook(const std::string& name) { m_newBookEvent.Trigger(name); }

  VLS::Event::IEventHandler<std::string>& NewBookEvent() const override {
    return m_newBookEvent;
  }

 private:
  // Mutable is used because subscribing to changes to an object should never
  // affect the functionality of the object The EventHandler class manages
  // subscriptions and can be used to trigger events using the template
  // parameters as arguments
  mutable VLS::Event::EventHandler<std::string> m_newBookEvent;
};
