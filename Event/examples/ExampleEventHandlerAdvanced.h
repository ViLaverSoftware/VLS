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

#include "BookPublisher.h"
#include "BookSubscriber.h"

using namespace std;

void ExampleEventHandlerAdvanced() {
  cout << "Example EventHandler Advanced" << endl;

  // Create a publisher with an event handler for new books
  BookPublisher publisher;

  // Create book subscribers
  auto subscriberA = make_unique<BookSubscriber>("A");
  auto subscriberB = make_unique<BookSubscriber>("B");

  // Subscribe to new publications
  subscriberA->SubscribeToPublications(publisher);
  subscriberB->SubscribeToPublications(publisher);

  cout << "> First book is published" << endl;
  publisher.AddBook("First book");

  // SubscriberA is removed and automaticly unsubscribes because the
  // VLS::Event::Subscriber object is dealocated
  subscriberA.reset();

  cout << "> Second book is published" << endl;
  publisher.AddBook("Second book");

  cout << endl;
}
