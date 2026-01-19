#pragma once

#include <string>
#include <vector>
#include <queue>
#include <time.h>

#include "components/simple_scene.h"
#include "components/transform.h"
#include "components/text_renderer.h"

#include "lab_m1/tema3/object.h"
#include "lab_m1/tema3/camera.h"

namespace t3 {
    class Tema3 : public gfxc::SimpleScene
    {
        public:
            Tema3();
            ~Tema3();

            void Init() override;

        private:
            void FrameStart() override;
            void Update(float deltaTimeSeconds) override;
            void FrameEnd() override;

            void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1 = NULL, float bendPhase = 0.f, float bendFrequency = 0.f);

            void OnInputUpdate(float deltaTime, int mods) override;
            void OnKeyPress(int key, int mods) override;
            void OnKeyRelease(int key, int mods) override;
            void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
            void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
            void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
            void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
            void OnWindowResize(int width, int height) override;

        protected:
            camera::Camera* camera;

            glm::mat4 projectionMatrix;
            bool renderCameraTarget = false;

            gfxc::TextRenderer* textRenderer;

            std::unordered_map<std::string, Texture2D*> mapTextures;
    };
}