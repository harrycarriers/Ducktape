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

#include <string>

#include <Core/Serialization.h>
#include <Scene/System.h>
#include <Scene/Scene.h>
#include <Core/Context.h>

namespace DT
{
    /**
     * @brief Tag struct for assigning tags on Entity objects
     */
    struct Tag
    {
        std::string name = "Unnamed"; ///< @brief Tag name
    };

    SERIALIZE(Tag, name);

    class TagSystem : public System
    {
    public:
        /**
         * @brief Serializes Tag properties for Inspector.
         */
        void Inspector(Scene *scene, const Context &ctx) override;

        /**
         * @brief Handles Tag serialization.
         */
        void Serialize(Scene *scene, const Context &ctx) override;
    };
}