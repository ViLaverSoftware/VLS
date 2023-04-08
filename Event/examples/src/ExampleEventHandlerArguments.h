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

void ExampleEventHandlerArguments() {
  cout << "Example EventHandler Arguments" << endl;

  // Create a event handler with two event arguments
  VLS::Event::EventHandler<std::string, int> valueChanged;

  // Subscribe to the event with a lambda function without an unsubscribe option
  valueChanged.SubscribePersistent([](const std::string& text, int number) {
    cout << text << " (" << number << ")" << endl;
  });

  // Trigger the event
  cout << "> Trigger event: ";
  valueChanged.Trigger("Hello World", 42);

  cout << endl;
}
