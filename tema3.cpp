#include "lab_m1/tema3/tema3.h"
#include "lab_m1/tema3/object.h"

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

    {
        Shader* shader = new Shader("VC");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
}

void Tema3::FrameStart() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema3::Update(float deltaTimeSeconds) {

}

void Tema3::FrameEnd() {
    // Code to execute at the end of each frame
}

void Tema3::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture) {
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    glUseProgram(shader->program);

    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glm::mat4 viewMatrix = camera->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    glm::mat4 projectionMatrix = this->projectionMatrix;
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void Tema3::OnInputUpdate(float deltaTime, int mods) {

}

void Tema3::OnKeyPress(int key, int mods) {

}

void Tema3::OnKeyRelease(int key, int mods) {

}

void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {

}

void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {

}

void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {

}

void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {

}

void Tema3::OnWindowResize(int width, int height) {

}
