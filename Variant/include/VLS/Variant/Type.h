/*
 * OakModelView (http://oakmodelview.com/)
 * Author: Mikkel N�hr L�vgreen (mikkel@oakmodelview.com)
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

namespace VLS::Variant {

enum class Type {
    Undefined = -1,
    Char = 0,
    Bool = 1,
    Integer = 2,
    Double = 3,
    String = 4,
    DateTime = 5
};

} // namespace VLS::Variant
