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
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "trunk1.jpg").c_str(), GL_REPEAT);
        mapTextures["bark"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "leaves.jpg").c_str(), GL_REPEAT);
        mapTextures["leaves"] = texture;
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "snowflake.jpg").c_str(), GL_REPEAT);
        mapTextures["snow"] = texture;
    }

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

        Mesh* leaves = object3D::CreateLeaves("leaves", glm::vec3(0, 0, 0));
        AddMeshToList(leaves);

        Mesh* terrain = object3D::CreateTerrain("terrain", glm::vec3(0, 0, 0));
        AddMeshToList(terrain);

        Mesh* tower = object3D::CreateObservationTower(meshes, "tower");
        AddMeshToList(tower);

        meshes["light_cone"] = object3D::CreatePyramid(meshes, "light_cone", 0.6f, 1.f, glm::vec3(0.1f, 0.1f, 0.1f));
    }
}

void Tema3::FrameStart() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema3::Update(float deltaTimeSeconds) {
    
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(8.f, 0, 1.f));
        RenderMesh(meshes["tree"], shaders["VC"], modelMatrix, mapTextures["bark"]);
        RenderMesh(meshes["leaves"], shaders["VC"], modelMatrix, mapTextures["leaves"], 0.2f, 0.6f);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(5.f, 0, -12.f));
        RenderMesh(meshes["tree"], shaders["VC"], modelMatrix, mapTextures["bark"]);
        RenderMesh(meshes["leaves"], shaders["VC"], modelMatrix, mapTextures["leaves"], 0.4f, 0.8f);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(7.f, 0, 12.f));
        RenderMesh(meshes["tree"], shaders["VC"], modelMatrix, mapTextures["bark"]);
        RenderMesh(meshes["leaves"], shaders["VC"], modelMatrix, mapTextures["leaves"], 0.1f, 0.5f);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-8.f, 0, 21.f));
        RenderMesh(meshes["tree"], shaders["VC"], modelMatrix, mapTextures["bark"]);
        RenderMesh(meshes["leaves"], shaders["VC"], modelMatrix, mapTextures["leaves"], 0.3f, 0.7f);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-14.f, 0, -8.f));
        RenderMesh(meshes["tree"], shaders["VC"], modelMatrix, mapTextures["bark"]);
        RenderMesh(meshes["leaves"], shaders["VC"], modelMatrix, mapTextures["leaves"], 0.8f, 0.2f);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-6.f, 0, -15.3f));
        RenderMesh(meshes["tree"], shaders["VC"], modelMatrix, mapTextures["bark"]);
        RenderMesh(meshes["leaves"], shaders["VC"], modelMatrix, mapTextures["leaves"], 0.7f, 0.3f);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.f, 0, 0.f));
        RenderMesh(meshes["terrain"], shaders["VC"], modelMatrix, mapTextures["snow"]);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.f, 0, 0.f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.8f, 0.5f));
        RenderMesh(meshes["tower"], shaders["VC"], modelMatrix);
    }

    {
        float angle1 = glm::radians(-30.0f);
        float angle2 = glm::radians(30.0f);

        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= glm::translate(glm::mat4(1), glm::vec3(0.f, 9.f, 1.5f));
        modelMatrix *= glm::rotate(glm::mat4(1), angle1, glm::vec3(1, 0, 0));
        RenderMesh(meshes["light_cone"], shaders["VC"], modelMatrix);

        modelMatrix = glm::mat4(1);
        modelMatrix *= glm::translate(glm::mat4(1), glm::vec3(0.f, 9.f, -1.5f));
        modelMatrix *= glm::rotate(glm::mat4(1), angle2, glm::vec3(1, 0, 0));
        RenderMesh(meshes["light_cone"], shaders["VC"], modelMatrix);
    }

    if (renderCameraTarget)
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
        RenderMesh(meshes["sphere"], shaders["VertexColor"], modelMatrix, mapTextures["snow"]);
    }
}

void Tema3::FrameEnd() {
    // Code to execute at the end of each fram
}

void Tema3::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1, float bendPhase, float bendFrequency) {
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    glUseProgram(shader->program);

    glUniformMatrix4fv(glGetUniformLocation(shader->program, "Model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shader->program, "View"), 1, GL_FALSE, glm::value_ptr(GetSceneCamera()->GetViewMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(shader->program, "Projection"), 1, GL_FALSE, glm::value_ptr(this->projectionMatrix));

    glUniform1f(glGetUniformLocation(shader->program, "time"), Engine::GetElapsedTime());

    int isTrunk = 0;
    int isLeaves = 0;
    int isSnow = 0;

    glUniform1f(glGetUniformLocation(shader->program, "treeHeight"), 5.0f);

    if (mesh == meshes["tree"]) {
        isTrunk = 1;
    } else if (mesh == meshes["leaves"]) {
        isLeaves = 1;
        glUniform1f(glGetUniformLocation(shader->program, "bendPhase"), bendPhase);
        glUniform1f(glGetUniformLocation(shader->program, "bendFrequency"), bendFrequency); 
    }

    glUniform1i(glGetUniformLocation(shader->program, "isTrunk"), isTrunk);
    glUniform1i(glGetUniformLocation(shader->program, "isLeaves"), isLeaves);

    if (texture1)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "texture1"), 0);
        glUniform1i(glGetUniformLocation(shader->program, "useTexture"), 1);
    } else {
        glUniform1i(glGetUniformLocation(shader->program, "useTexture"), 0);
    }

    glUniform3fv(glGetUniformLocation(shader->program, "fogColor"), 1, glm::value_ptr(glm::vec3(0.7f, 0.7f, 0.75f)));
    glUniform1f(glGetUniformLocation(shader->program, "fogStart"), 10.0f);
    glUniform1f(glGetUniformLocation(shader->program, "fogEnd"), 40.0f);
    glUniform3fv(glGetUniformLocation(shader->program, "cameraPos"), 1, glm::value_ptr(GetSceneCamera()->m_transform->GetWorldPosition()));

    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<GLsizei>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
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
