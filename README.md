# VLS
VLS is a open source software library created by ViLaverSoftware IVS.

# Vision
I hope this will become a opensource library with multipe components of production ready quality usefull to many.

# Components
I have alot of components planned, but making software of production ready quality takes a long time, so I will take one component at a time.
All comments good and bad are more than wellcome. 

## Event
EventHandler - Variadric template class that can handle events with any argument (arguments match the variadric template of the class).
 * Subscriptions are made with callables.
 * Multiple subscriptions are supported.
 * Smart unsubscription functionality. 
 * Subscription functions are Exposed with an interface IEventHandler.
 * Async calling of callables are supported

 EventLoop - Wrapper of a std::thread where tasks can be enqueued as void(void) callables. It is used to call callables on an async when an event is triggered.

 Status - Component is mostly done but some documentation is still missing and more unit/integration tests.


# License
Copyright 2020 Vilaversoftware IVS (http://vilaversoftware.dk/)
Author: Mikkel Nøhr Løvgreen (ml@vilaversoftware.dk)
------------------------------------------------------------------------
Licensed to Vilaversoftware IVS who licenses this file to you under the
Apache License, Version 2.0 (the "License"); you may not use this file
except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.