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

#include "VLS/Event/EventHandler.h"

using namespace std;

void ExampleEventHandlerUnsubscribe() {
  cout << "Example EventHandler Unsubscribe" << endl;

  // Description: VLS::Event::Subscriber description
  // Subscriber objects can be linked to subscriptions. When the subscriber
  // object is dealocated it automaticly unsubscribe from the linked events.
  // Subscriber objects also have an UnsubscribeAll() function that can be used
  // to manually unsubscribe from events linked to it.

  // Create a event handler
  VLS::Event::EventHandler<> valueChanged;

  // Option 1: It is not possible to unsubscribe with subscribe Persistent
  // This is the easiest option if the event reciever lives at least as long as
  // the event handler.
  valueChanged.SubscribePersistent(
      []() { cout << "> Subscribe Persistent Event" << endl; });

  // Option 2: This returns an unique pointer to a subscriber object.
  // This is the easiest option when having one subscriber object pr.
  // subscription.
  VLS::Event::Subscriber::UPtr returnSubscriber = valueChanged.Subscribe(
      []() { cout << "> Return Subscriber  Event" << endl; });

  // Option 3: Provide a subscriber object that gets linked with the
  // subscription. This is the easiest option when having one subscriber for
  // multiple subscriptions.
  VLS::Event::Subscriber provideSubscriber;
  valueChanged.Subscribe(provideSubscriber, []() {
    cout << "> Provide Subscriber Event 1" << endl;
  });
  valueChanged.Subscribe(provideSubscriber, []() {
    cout << "> Provide Subscriber Event 2" << endl;
  });

  // Trigger the event with all subscriptions active
  cout << "> Trigger event (All): " << endl;
  valueChanged.Trigger();

  provideSubscriber.UnsubscribeAll();
  cout << "> Trigger event (Manual Unsubscribe):" << endl;
  valueChanged.Trigger();

  returnSubscriber.reset();
  cout << "> Trigger event (Automatic Unsubscribe):" << endl;
  valueChanged.Trigger();

  cout << endl;
}
