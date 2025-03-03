/*
Ducktape | An open source C++ 2D & 3D game engine that focuses on being fast, and powerful.
Copyright (C) 2022 Aryan Baburajan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

In case of any further questions feel free to contact me at
the following email address:
aryanbaburajan2007@gmail.com
*/

#pragma once

#include <assert.h>
#include <iostream>
#include <string>
#include <filesystem>

#define DT_ASSERT(condition, message)                                                                     \
    do                                                                                                    \
    {                                                                                                     \
        if (condition == false)                                                                           \
        {                                                                                                 \
            std::cout << "Assertion failed: " + std::string(message) << '\n'                              \
                      << "In file: " << std::string(__FILE__) << ":" << std::to_string(__LINE__) << '\n'; \
            exit(1);                                                                                      \
        }                                                                                                 \
    } while (0)

/* This macro expression gets optimized out during compilation, but will
 * satisfy the compiler from complaining about unused variables
 */
#define UNUSED(expr)  \
    do                \
    {                 \
        (void)(expr); \
    } while (0)

#define DUCKTAPE_ROOT_DIR std::filesystem::current_path().parent_path()

// Source: https://stackoverflow.com/questions/257288/templated-check-for-the-existence-of-a-class-member-function
#define HAS_METHOD_DECL(methodName)                            \
    template <typename CheckType>                              \
    class Has##methodName                                      \
    {                                                          \
        typedef char One;                                      \
        struct Two                                             \
        {                                                      \
            char x[2];                                         \
        };                                                     \
        template <typename C>                                  \
        static One Test(decltype(&C::methodName));             \
        template <typename C>                                  \
        static Two Test(...);                                  \
                                                               \
    public:                                                    \
        enum                                                   \
        {                                                      \
            value = sizeof(Test<CheckType>(0)) == sizeof(char) \
        };                                                     \
    };
