/*
Ducktape | An open source C++ 2D & 3D game Engine that focuses on being fast, and powerful.
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

#define DT_DEBUG

#include <Core/Engine.h>
#include <Components/RegisterComponentSystems.h>
#include <Editor.h>
#include <Panels/ConsolePanel.h>
#include <Panels/ScenePanel.h>
#include <Panels/PropertiesPanel.h>
#include <Panels/MenuBarPanel.h>
#include <Panels/ProjectPanel.h>
#include <Panels/ResourceBrowserPanel.h>
#include <Panels/ResourceInspectorPanel.h>
#include <Panels/ResourceInterface.h>
#include <Panels/SceneViewPanel.h>
#include <Panels/DucktapeEditorPanel.h>
#include <Panels/AssignComponentMenuPanel.h>
#include <Panels/RemoveComponentMenuPanel.h>
using namespace DT;

int main()
{
    try
    {
        Engine e(Project(DUCKTAPE_ROOT_DIR / "Resources" / "Sandbox"));

        Scene mainScene(e.project.config);

        RegisterComponentSystems(mainScene);

        // std::cout << __LINE__ << std::endl;
        // SceneManager::Load(e.project.directory / "Assets" / "Scenes" / "MainScene.json", mainScene, e);
        // std::cout << __LINE__ << std::endl;

        Entity camera = mainScene.CreateEntity();
        mainScene.Assign<Tag>(camera).name = "Camera";
        mainScene.Assign<Transform>(camera);
        mainScene.Assign<Camera>(camera);
        mainScene.Assign<DirectionalLight>(camera);

        // for (const auto &meshAsset : std::filesystem::directory_iterator(e.project.directory / "Assets" / "Models" / "backpack" / "backpack"))
        //     if (!meshAsset.is_directory())
        //         mainScene.Assign<MeshRenderer>(mainScene.CreateEntity()).mesh = ResourceManager::GetRID(meshAsset);

        e.loopManager.sceneTick = false;

        e.Init(mainScene);

        Editor::AddPanel<SceneViewPanel>();
        Editor::AddPanel<ScenePanel>();
        Editor::AddPanel<ResourceBrowserPanel>();
        Editor::AddPanel<ResourceInspectorPanel>();
        Editor::AddPanel<ConsolePanel>();
        Editor::AddPanel<PropertiesPanel>();
        Editor::AddPanel<MenuBarPanel>();
        Editor::AddPanel<ProjectPanel>();
        Editor::AddPanel<DucktapeEditorPanel>();
        Editor::AddPanel<AssignComponentMenuPanel>();
        Editor::AddPanel<RemoveComponentMenuPanel>();
        ResourceInterface::AddDefault();

        Editor::Init(e);

        while (e.IsOpen())
        {
            e.PollEvents();

            if (!e.IsOpen())
                break;

            e.StartFrame();
            // std::cout << "StartFrame\n";

            Editor::NewFrame();
            // std::cout << "NewFrame\n";

            for (System *system : mainScene.GetSystems())
                system->SceneView(&mainScene, e.ctx);
            // std::cout << "SceneView\n";

            Editor::Render(e);
            // std::cout << "Render\n";

            Editor::EndFrame(e.renderer);
            // std::cout << "EndFrame\n";
            e.EndFrame();
            // std::cout << "EndFrame\n";
        }

        e.project.Save();
        Editor::Terminate();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        std::cin.get();
    }
}