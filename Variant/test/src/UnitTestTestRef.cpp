/*
 * VLS (http://vilaversoftware.dk/)
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

#pragma warning(push, 0)
#include "gtest/gtest.h"
#pragma warning(pop)

#include <iostream>

#include "VLS/Variant/TestRef.h"

using namespace VLS::Variant;

class cat {
public:
    void speak() {
        std::cout << "cat speaks" << std::endl;
    }
};

class dog {
public:
    void speak() {
        std::cout << "dog speaks" << std::endl;
    }
};

TEST(VLSVariantTestRef, Constructor)
{
    animal a = cat{};
    a.speak();
    a = dog{};
    a.speak();
}
