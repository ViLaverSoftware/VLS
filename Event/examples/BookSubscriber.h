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

#include <iostream>

#include "IBookPublisher.h"

class BookSubscriber : private VLS::Event::Subscriber {
 public:
  BookSubscriber(const std::string& name) : m_name(name) {}

  void SubscribeToPublications(const IBookPublisher& bookPublisher) {
    // Subscribe with a member function
    bookPublisher.NewBookEvent().Subscribe(
        m_subscriber,
        VLS::Event::Func::Bind(this, &BookSubscriber::OnNewBookPublished));
  }

 private:
  void OnNewBookPublished(const std::string& bookName) {
    std::cout << "> Subscriber " << m_name
              << " received a new book: " << bookName << std::endl;
  }

  // The subscriber class can hold event subscriptions and it will automatically
  // unsubscribe when deallocated.
  VLS::Event::Subscriber m_subscriber;

  std::string m_name;
};
