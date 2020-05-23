# VLS
VLS is an open source C++ software library created by ViLaverSoftware IVS.
I Mikkel Nøhr Løvgreen is the owner and only employee of ViLaverSoftware IVS.

The VLS open source library is developed in synergy with the primary activity of 
ViLaverSoftware which is freelance work as a consultant. 
Knowledge and inspiration for VLS is gained from freelance consultancy work.
The VLS library is meant to provide a toolbox that I and everyone else can use. 
Working with ideas and exploring the possibilities of the C++ language also 
gives valuable experience I can use for my freelance consultancy work.


# Vision
VLS will be an open source library of production ready components. Other 
developers will point out weaknesses and come with suggestions to improvements
so together we can create great software. 


# Components
Making production ready code takes time and time is always in short supply. 
Many components are planned and under development but they will still come 
into this library slowly.
All comments good and bad are more than welcome. It is my hope that someone 
will find this useful :)


## Event
The event component of VLS is meant to help implement events (callbacks). Qt 
have signal slots to do this but not everyone want Qt in their code or at least 
not in all of their code.
The functionality is contained in two classes. EventHandler and EventLoop.


### EventHandler
Variadic template class that can handle events with any argument (arguments 
match the variadic template of the class).
 * Subscriptions are made with callables.
 * Multiple subscriptions are supported.
 * Smart unsubscription functionality. 
 * Subscription functions are Exposed with an interface IEventHandler.
 * Async calling of callables are supported

 ### EventLoop
 Wrapper of a std::thread where tasks can be enqueued as void(void) callables. 
 It is used to call callables async when an event is triggered.

 ### Status
 Component is mostly done but some documentation is still missing and 
 more unit/integration tests.


# Fundamental Software Development Guidelines
Most developers with half a year experience can create a descent application 
in 2 month time. The problems starts when that software needs to be continuously 
upgraded and more developers needs to work on the same project. 
The code ends up as one large bowl of spaghetti with one patch on top of an 
other. The original design no longer fits, and when one issue is fix an other 
is created. Know one have the full understanding of what each part of the code 
does and it is extremely hard to learn. At some point 70% or more of the time 
is use to bug fix.

This is for me the most important challenge to overcome but it is not easy.

Software is complex and no matter what we do it will never be simple, but
as software developers we can do our best to make it as easy as possible to
understand our code.
The best way I have found to do this is to split the code up into components
with as simple as possible interface. If a large very complex application is 
made of many components with clear simple interfaces and a clear purpose. Then
It will be possible to understand the interaction between components without 
understanding how each component works. 


# Available C++ Software Library
C++ needs to be build with the same runtime to be binary compatible. External 
libraries can therefore cause a lot of problems during linking if they are not 
build along side the rest of the application. 
Providing the source as open source makes it possible but having the right 
build system and a package manager can make the process smooth.


## Build system - CMake
VLS uses CMake because it is cross platform and it the most commonly used C++
build system even though it is actually a build system generator.
It is the goal to make it easy to integrate into other applications. If it is
not the case raise any issues. 


## Package manager - Conan
Conan is currently used to get external dependencies (gtest) and a recipe 
will be added soon.
If changes are needed so other package manager can be supported please feel 
free to make suggestions. I will try not to implement too many features no 
one needs. 


# Project Directory Structure
The directory structure is chosen to support a large library with 20+ 
components. At the moment there are one so it might be a bit overkill but
I like to use my learnings and be prepared. 
All component will be placed in a flat directory structure to give an easy
overview. The top level directory of each component will be named after its 
namespace. 
 * namespace: VLS::Event     - Directory: Event
 * namespace: VLS::Event::Qt - Directory: Event.Qt


# Definitions
Many terms can be understood many ways. Here I list a few to be more clear. 


## Production Ready Code
Code is tested with unit/integration test, documented with good reference 
documentation and made available.


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