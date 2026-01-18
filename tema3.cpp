#include "lab_m1/tema3/tema3.h"
#include "lab_m1/tema3/object.h"
#include "lab_m1/tema3/camera.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace t3;

Tema3::Tema3() {
}

Tema3::~Tema3() {
}

void Tema3::Init() {
    camera = new camera::Camera();
    camera->Set(glm::vec3(0, 2, 5), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    renderCameraTarget = false;

    const string sourceTextureDir = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema3", "textures");
    projectionMatrix = glm::perspective(RADIANS(60.0f), window->props.aspectRatio, 0.01f, 200.0f);

    {
        Shader* shader = new Shader("VC");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema3", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema3", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;

        Mesh* tree = object3D::CreateTree("tree", glm::vec3(0, 0, 0));
        AddMeshToList(tree);
    }

    {
        glm::ivec2 windowResolution = window->GetResolution();
        textRenderer = new gfxc::TextRenderer(window->props.selfDir, windowResolution.x, windowResolution.y);
        textRenderer->Load("../assets/fonts/Hack-Bold.ttf", 20);
    }
}

void Tema3::FrameStart() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);

    DrawCoordinateSystem();
}

void Tema3::Update(float deltaTimeSeconds) {
    glm::mat4 modelMatrix = glm::mat4(1);

    {
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
        RenderMesh(meshes["tree"], shaders["VertexColor"], modelMatrix);
    }

    if (renderCameraTarget)
    {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
        RenderMesh(meshes["sphere"], shaders["VertexColor"], modelMatrix);
    }
}

void Tema3::FrameEnd() {
    // Code to execute at the end of each fram
}

void Tema3::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture) {
    if (!mesh || !shader || !shader->GetProgramID()) {
        return;
    }

    glUseProgram(shader->program);

    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glm::mat4 viewMatrix = camera->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    glm::mat4 projectionMatrix = this->projectionMatrix;
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    GLint useTexture = glGetUniformLocation(shader->program, "useTexture");

    if (texture)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "texture1"), 0);
        glUniform1i(useTexture, 1);
    }
    else {
        glUniform1i(useTexture, 0);
    }

    mesh->Render();
}

void Tema3::OnInputUpdate(float deltaTime, int mods) {
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float cameraSpeed = 5.0f;

        if (window->KeyHold(GLFW_KEY_W)) {
            camera->MoveForward(cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_A)) {
            camera->TranslateRight(-cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            camera->MoveForward(-cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            camera->TranslateRight(cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_Q)) {
            camera->TranslateUpward(-cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_E)) {
            camera->TranslateUpward(cameraSpeed * deltaTime);
        }
    }
}

void Tema3::OnKeyPress(int key, int mods) {
    if (key == GLFW_KEY_T) {
        renderCameraTarget = !renderCameraTarget;
    }
}

void Tema3::OnKeyRelease(int key, int mods) {

}

void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->GetSpecialKeyState() == 0) {
            renderCameraTarget = false;
            camera->RotateFirstPerson_OY(-deltaX * sensivityOY);
            camera->RotateFirstPerson_OX(-deltaY * sensivityOX);
        }

        if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
            renderCameraTarget = true;
            camera->RotateThirdPerson_OX(-deltaY * sensivityOX);
            camera->RotateThirdPerson_OY(-deltaX * sensivityOY);
        }
    }
}

void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {

}

void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {

}

void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {

}

void Tema3::OnWindowResize(int width, int height) {

}
