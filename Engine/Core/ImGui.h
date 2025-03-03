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

#include <vector>
#include <string>

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/misc/cpp/imgui_stdlib.h>
#include <glm/glm.hpp>
#include <imgui/ImGuizmo.h>
#include <imgui/imfilebrowser.h>

#include <Renderer/Mesh.h>
#include <Renderer/Material.h>
#include <Core/ResourceManager.h>
#include <Core/Resource.h>

namespace ImGui
{
    inline FileBrowser fileDialog(ImGuiFileBrowserFlags_CloseOnEsc);

    IMGUI_API void Material(const std::string &label, DT::Material *material);
    IMGUI_API void Vec3(const std::string &label, glm::vec3 *vec3);
    IMGUI_API void Vec2(const std::string &label, glm::vec2 *vec2);
    IMGUI_API bool ImageButtonWithText(ImTextureID texId, const char *label, const ImVec2 &imageSize = ImVec2(0, 0), bool wrapContent = false, const ImVec2 &uv0 = ImVec2(0, 0), const ImVec2 &uv1 = ImVec2(1, 1), int frame_padding = -1, const ImVec4 &bg_col = ImVec4(0, 0, 0, 0), const ImVec4 &tint_col = ImVec4(1, 1, 1, 1));
    IMGUI_API void AlignForWidth(float width, float alignment = 0.5f);
    IMGUI_API void Color(const std::string &label, glm::vec3 *color);
    IMGUI_API void Color(const std::string &label, glm::vec4 *color);
    IMGUI_API bool ImageWithInputText(ImTextureID texId, const char *label, char *buf, size_t buf_size, const ImVec2 &imageSize = ImVec2(0, 0), const ImVec2 &uv0 = ImVec2(0, 0), const ImVec2 &uv1 = ImVec2(1, 1), bool wrapContent = false, int frame_padding = -1, const ImVec4 &bg_col = ImVec4(0, 0, 0, 0), const ImVec4 &tint_col = ImVec4(1, 1, 1, 1));

    ImVec2 operator*(ImVec2 &iv2, float fl);
    ImVec2 operator*(const ImVec2 &iv2, float fl);
    ImVec2 operator*(ImVec2 &iv2, int i);
    ImVec2 operator+(ImVec2 &iv2, ImVec2 &otheriv2);
    ImVec2 operator+(const ImVec2 &iv2, const ImVec2 &otheriv2);

    template <typename T>
    IMGUI_API void Resource(const std::string &label, DT::Resource<T> *resource)
    {
        ImGuiWindow *window = GetCurrentWindow();
        if (window->SkipItems)
            return;

        DT::ResourceManager &rm = DT::ResourceManager::Instance();

        BeginGroup();
        PushID(label.c_str());

        if (ImGui::Button(rm.GetPath(resource->rid).filename().string().c_str(), ImVec2(ImGui::GetWindowSize().x * 0.65f, 0.0f)))
        {
            fileDialog.Open();
            fileDialog.SetTitle(label);
            // fileDialog.SetTypeFilters() // Implement resource type identifiers
        }

        if (fileDialog.HasSelected())
        {
            resource->rid = DT::ResourceManager::GetRID(fileDialog.GetSelected());
            fileDialog.ClearSelected();
        }

        ImGui::SameLine();

        ImGui::Text(label.c_str());

        PopID();
        EndGroup();
    }
}