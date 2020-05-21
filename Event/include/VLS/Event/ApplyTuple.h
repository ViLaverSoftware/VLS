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

namespace VLS::Event {

/// <summary>
/// Object Function Tuple Argument Unpacking
/// This recursive template unpacks the tuple parameters into variadic
/// template arguments until it reach the count of 0 where the function
/// is called with the correct parameters.
/// </summary>
/// <param name="N"> Number of tuple arguments to unroll </param>
template<unsigned int N>
struct ApplyTupleObjFunc
{
    template<typename T, typename... ArgsF, typename... ArgsT, typename... Args>
    static void ApplyTuple(T* pObj, void (T::* f)(ArgsF...), const std::tuple<ArgsT...>& t, Args... args) {
        ApplyTupleObjFunc<N - 1>::ApplyTuple(pObj, f, t, std::get<N - 1>(t), args...);
    }
};

/// <summary>
/// Object Function Tuple Argument Unpacking
/// This recursive template unpacks the tuple parameters into variadic
/// template arguments until it reach the count of 0 where the function
/// is called with the correct parameters.
/// </summary>
template <>
struct ApplyTupleObjFunc<0>
{
    template < typename T, typename... ArgsF, typename... ArgsT, typename... Args >
    static void ApplyTuple(T* pObj, void (T::* f)(ArgsF...), const std::tuple<ArgsT...>&, Args... args) {
        (pObj->*f)(args...);
    }
};

/// <summary>
/// Calls a function with arguments that match the values of a tuple
/// The tuple is unpacked into a sequence of arguments usign the ApplyTupleObjFunc. 
/// </summary>
/// <param name="pObj"> Pointer to object owning the function </param>
/// <param name="func"> Pointer to the function that will be called with tuple data </param>
/// <param name="tuple"> Reference to tuple containing the data </param>
template<typename T, typename... ArgsF, typename... ArgsT>
void ApplyTuple(T* pObj, void (T::* func)(ArgsF...), std::tuple<ArgsT...> const& tuple) {
    ApplyTupleObjFunc<sizeof...(ArgsT)>::ApplyTuple(pObj, func, tuple);
}

}