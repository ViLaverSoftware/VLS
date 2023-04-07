# VLS Libray {#vls}
Version 1.0.0

The VLS Library is an open source C++ software library created by ViLaverSoftware.

For more than 12 years I have been developing C++ software and have used lots of great open source libraries. 
Working on VLS Library is my way of trying to give something useful back to the community.
I will do my very best to provide software of the highest quality so all bug reports, improvement suggestions or comments are very welcome. 


## Official Homepage
*http://www.vilaversoftware.dk*

Contains getting started guide, descriptions and examples.


## Modules
VLS Library currently contains a single module but more modules are planned. 

 * [Event Module](@ref event)

 ## Platforms
 The VLS Library only use the standard library and do not include any system headers.

 It should therefore be platform independent but have only been tested on windows. 


 ## Requirements
 The goal is to keep dependencies as low as possible.

 Library dependencies:
 - CMake
 - C++20

 Test additional dependencies:
  - Conan package manager
  - GTest
  
## Conan package manager
Install python3:
 - https://www.python.org/downloads/

Install Conan using pip:
 - Open command prompt
 - pip install conan
 
Create conan profile:
 - conan profile detect --force
 
Edit conan profile:
 - ~/.conan2/profiles/default

Find conan package:
- https://conan.io/center/



## License
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
