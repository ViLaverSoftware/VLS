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

void FreeFunction() { cout << "> Free Function" << endl; }

class ExampleClass {
 public:
  void MemberFunction() { cout << "> Member Function" << endl; }
};

void ExampleEventHandlerCallbackFunctions() {
  cout << "Example EventHandler Callback Functions" << endl;

  // Create a event handler
  VLS::Event::EventHandler<> valueChanged;

  // Subscribe to the event with a free function
  valueChanged.SubscribePersistent(&FreeFunction);

  // Subscribe to the event with a member function
  ExampleClass eClass;
  valueChanged.SubscribePersistent(
      VLS::Event::Func::Bind(&eClass, &ExampleClass::MemberFunction));

  // Subscribe to the event with a lambda function
  valueChanged.SubscribePersistent(
      []() { cout << "> Lambda Function" << endl; });

  // Trigger the event
  valueChanged.Trigger();

  cout << endl;
}
