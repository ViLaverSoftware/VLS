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

#include <functional>

namespace VLS::Event {

/// <sammary> Binds member functions to callables. </summary>
/// <remarks>
/// Class with static functions that create a callable std::function<void(...)> from a member function with the same parameters.
/// Any member function with 0 to 9 arguments can be bound in a callable with the same arguments. 
/// </remarks>
class Func {
public:
    /// <summary>
    /// Create a callable std::function<void(void)> from a void(void) member function.
    /// </summary>
    /// <typeparam  name="TObj"> Class of the funcObj. </typeparam >
    /// <param name="funcObj"> Object the function belongs to. </param>
    /// <param name="func"> Member function pointer with no arguments. </param>
    /// <returns> Callable that returns void and takes no parameters. </returns>
    template<typename TObj>
    static std::function<void()> Bind(TObj* funcObj, void (TObj::* func)())
    {
        return std::bind(func, funcObj);
    }

    /// <summary>
    /// Create a callable std::function<void(T)> from a void(T) member function.
    /// </summary>
    /// <typeparam  name="TObj"> Class of the funcObj. </typeparam >
    /// <typeparam  name="T"> Type of the function argument. </typeparam >
    /// <param name="funcObj"> Object the function belongs to. </param>
    /// <param name="func"> Member function pointer with one argument. </param>
    /// <returns> Callable that returns void and takes one parameter. </returns>
    template<typename TObj, typename T>
    static std::function<void(T)> Bind(TObj* funcObj, void (TObj::* func)(T))
    {
        return std::bind(func, funcObj, std::placeholders::_1);
    }

    /// <summary>
    /// Create a callable std::function<void(T1, T2)> from a void(T1, T2) member function.
    /// </summary>
    /// <typeparam  name="TObj"> Class of the funcObj. </typeparam >
    /// <typeparam  name="T1"> Type of the 1. function argument. </typeparam >
    /// <typeparam  name="T2"> Type of the 2. function argument. </typeparam >
    /// <param name="funcObj"> Object the function belongs to. </param>
    /// <param name="func"> Member function pointer with two arguments. </param>
    /// <returns> Callable that returns void and takes two parameters. </returns>
    template<typename TObj, typename T1, typename T2>
    static std::function<void(T1, T2)> Bind(TObj* funcObj, void (TObj::* func)(T1, T2))
    {
        return std::bind(func, funcObj, std::placeholders::_1, std::placeholders::_2);
    }

    /// <summary>
    /// Create a callable std::function<void(T1, T2, T3)> from a void(T1, T2, T3) member function.
    /// </summary>
    /// <typeparam  name="TObj"> Class of the funcObj. </typeparam >
    /// <typeparam  name="T1"> Type of the 1. function argument. </typeparam >
    /// <typeparam  name="T2"> Type of the 2. function argument. </typeparam >
    /// <typeparam  name="T3"> Type of the 3. function argument. </typeparam >
    /// <param name="funcObj"> Object the function belongs to. </param>
    /// <param name="func"> Member function pointer with three arguments. </param>
    /// <returns> Callable that returns void and takes three parameters. </returns>
    template<typename TObj, typename T1, typename T2, typename T3>
    static std::function<void(T1, T2, T3)> Bind(TObj* funcObj, void (TObj::* func)(T1, T2, T3))
    {
        return std::bind(func, funcObj, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    }

    /// <summary>
    /// Create a callable std::function<void(T1, T2, T3, T4)> from a void(T1, T2, T3, T4) member function.
    /// </summary>
    /// <typeparam  name="TObj"> Class of the funcObj. </typeparam >
    /// <typeparam  name="T1"> Type of the 1. function argument. </typeparam >
    /// <typeparam  name="T2"> Type of the 2. function argument. </typeparam >
    /// <typeparam  name="T3"> Type of the 3. function argument. </typeparam >
    /// <typeparam  name="T4"> Type of the 4. function argument. </typeparam >
    /// <param name="funcObj"> Object the function belongs to. </param>
    /// <param name="func"> Member function pointer with four arguments. </param>
    /// <returns> Callable that returns void and takes four parameters. </returns>
    template<typename TObj, typename T1, typename T2, typename T3, typename T4>
    static std::function<void(T1, T2, T3, T4)> Bind(TObj* funcObj, void (TObj::* func)(T1, T2, T3, T4))
    {
        return std::bind(func, funcObj, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
    }

    /// <summary>
    /// Create a callable std::function<void(T1, T2, T3, T4, T5)> from a void(T1, T2, T3, T4, T5) member function.
    /// </summary>
    /// <typeparam  name="TObj"> Class of the funcObj. </typeparam >
    /// <typeparam  name="T1"> Type of the 1. function argument. </typeparam >
    /// <typeparam  name="T2"> Type of the 2. function argument. </typeparam >
    /// <typeparam  name="T3"> Type of the 3. function argument. </typeparam >
    /// <typeparam  name="T4"> Type of the 4. function argument. </typeparam >
    /// <typeparam  name="T5"> Type of the 5. function argument. </typeparam >
    /// <param name="funcObj"> Object the function belongs to. </param>
    /// <param name="func"> Member function pointer with five arguments. </param>
    /// <returns> Callable that returns void and takes five parameters. </returns>
    template<typename TObj, typename T1, typename T2, typename T3, typename T4, typename T5>
    static std::function<void(T1, T2, T3, T4, T5)> Bind(TObj* funcObj, void (TObj::* func)(T1, T2, T3, T4, T5))
    {
        return std::bind(func, funcObj, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5);
    }

    /// <summary>
    /// Create a callable std::function<void(T1, T2, T3, T4, T5, T6)> from a void(T1, T2, T3, T4, T5, T6) member function.
    /// </summary>
    /// <typeparam  name="TObj"> Class of the funcObj. </typeparam >
    /// <typeparam  name="T1"> Type of the 1. function argument. </typeparam >
    /// <typeparam  name="T2"> Type of the 2. function argument. </typeparam >
    /// <typeparam  name="T3"> Type of the 3. function argument. </typeparam >
    /// <typeparam  name="T4"> Type of the 4. function argument. </typeparam >
    /// <typeparam  name="T5"> Type of the 5. function argument. </typeparam >
    /// <typeparam  name="T6"> Type of the 6. function argument. </typeparam >
    /// <param name="funcObj"> Object the function belongs to. </param>
    /// <param name="func"> Member function pointer with six arguments. </param>
    /// <returns> Callable that returns void and takes six parameters. </returns>
    template<typename TObj, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    static std::function<void(T1, T2, T3, T4, T5, T6)> Bind(TObj* funcObj, void (TObj::* func)(T1, T2, T3, T4, T5, T6))
    {
        return std::bind(func, funcObj, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6);
    }

    /// <summary>
    /// Create a callable std::function<void(T1, T2, T3, T4, T5, T6, T7)> from a void(T1, T2, T3, T4, T5, T6, T7) member function.
    /// </summary>
    /// <typeparam  name="TObj"> Class of the funcObj. </typeparam >
    /// <typeparam  name="T1"> Type of the 1. function argument. </typeparam >
    /// <typeparam  name="T2"> Type of the 2. function argument. </typeparam >
    /// <typeparam  name="T3"> Type of the 3. function argument. </typeparam >
    /// <typeparam  name="T4"> Type of the 4. function argument. </typeparam >
    /// <typeparam  name="T5"> Type of the 5. function argument. </typeparam >
    /// <typeparam  name="T6"> Type of the 6. function argument. </typeparam >
    /// <typeparam  name="T7"> Type of the 7. function argument. </typeparam >
    /// <param name="funcObj"> Object the function belongs to. </param>
    /// <param name="func"> Member function pointer with seven arguments. </param>
    /// <returns> Callable that returns void and takes seven parameters. </returns>
    template<typename TObj, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    static std::function<void(T1, T2, T3, T4, T5, T6, T7)> Bind(TObj* funcObj, void (TObj::* func)(T1, T2, T3, T4, T5, T6, T7))
    {
        return std::bind(func, funcObj, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7);
    }

    /// <summary>
    /// Create a callable std::function<void(T1, T2, T3, T4, T5, T6, T7, T8)> from a void(T1, T2, T3, T4, T5, T6, T7, T8) member function.
    /// </summary>
    /// <typeparam  name="TObj"> Class of the funcObj. </typeparam >
    /// <typeparam  name="T1"> Type of the 1. function argument. </typeparam >
    /// <typeparam  name="T2"> Type of the 2. function argument. </typeparam >
    /// <typeparam  name="T3"> Type of the 3. function argument. </typeparam >
    /// <typeparam  name="T4"> Type of the 4. function argument. </typeparam >
    /// <typeparam  name="T5"> Type of the 5. function argument. </typeparam >
    /// <typeparam  name="T6"> Type of the 6. function argument. </typeparam >
    /// <typeparam  name="T7"> Type of the 7. function argument. </typeparam >
    /// <typeparam  name="T8"> Type of the 8. function argument. </typeparam >
    /// <param name="funcObj"> Object the function belongs to. </param>
    /// <param name="func"> Member function pointer with eight arguments. </param>
    /// <returns> Callable that returns void and takes eight parameters. </returns>
    template<typename TObj, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
    static std::function<void(T1, T2, T3, T4, T5, T6, T7, T8)> Bind(TObj* funcObj, void (TObj::* func)(T1, T2, T3, T4, T5, T6, T7, T8))
    {
        return std::bind(func, funcObj, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8);
    }

    /// <summary>
    /// Create a callable std::function<void(T1, T2, T3, T4, T5, T6, T7, T8, T9)> from a void(T1, T2, T3, T4, T5, T6, T7, T8, T9) member function.
    /// </summary>
    /// <typeparam  name="TObj"> Class of the funcObj. </typeparam >
    /// <typeparam  name="T1"> Type of the 1. function argument. </typeparam >
    /// <typeparam  name="T2"> Type of the 2. function argument. </typeparam >
    /// <typeparam  name="T3"> Type of the 3. function argument. </typeparam >
    /// <typeparam  name="T4"> Type of the 4. function argument. </typeparam >
    /// <typeparam  name="T5"> Type of the 5. function argument. </typeparam >
    /// <typeparam  name="T6"> Type of the 6. function argument. </typeparam >
    /// <typeparam  name="T7"> Type of the 7. function argument. </typeparam >
    /// <typeparam  name="T8"> Type of the 8. function argument. </typeparam >
    /// <typeparam  name="T9"> Type of the 9. function argument. </typeparam >
    /// <param  name="funcObj"> Object the function belongs to. </param >
    /// <param name="func"> Member function pointer with nine arguments. </param>
    /// <returns> Callable that returns void and takes nine parameters. </returns>
    template<typename TObj, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
    static std::function<void(T1, T2, T3, T4, T5, T6, T7, T8, T9)> Bind(TObj* funcObj, void (TObj::* func)(T1, T2, T3, T4, T5, T6, T7, T8, T9))
    {
        return std::bind(func, funcObj, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6, std::placeholders::_7, std::placeholders::_8, std::placeholders::_9);
    }
};

}
