#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

#define YELLOW_COLOR glm::vec3(1.0f, 1.f, 0.f)
#define GREEN_COLOR glm::vec3(0.f, 1.f, 0.f)
#define DARK_GREEN_COLOR glm::vec3(0.f, 0.5f, 0.f)
#define BLUE_COLOR glm::vec3(0.f, 0.f, 1.f)
#define PURPLE_COLOR glm::vec3(1.f, 0.f, 1.f)
#define RED_COLOR glm::vec3(1.f, 0.f, 0.f)
#define GRAY_COLOR glm::vec3(0.75f, 0.75f, 0.75f)
#define LIGHT_GRAY_COLOR glm::vec3(0.9f, 0.9f, 0.9f)
#define DARK_GRAY_COLOR glm::vec3(0.2f, 0.2f, 0.2f)
#define WHITE_COLOR glm::vec3(1.f, 1.f, 1.f)
#define ORANGE_COLOR glm::vec3(0.8f, 0.5f, 0.2f)
#define BROWN_COLOR glm::vec3(0.4f, 0.25f, 0.07f)

namespace object3D {
    Mesh* CreateTree(const std::string& name, glm::vec3 center);

    Mesh* CreateLeaves(const std::string& name, glm::vec3 center);

    Mesh* CreateTerrain(const std::string& name, glm::vec3 center);

    Mesh* CreateObservationTower(std::unordered_map<std::string, Mesh*>& meshes, const char* name);

    Mesh* CreatePyramid(std::unordered_map<std::string, Mesh*>& meshes, const char* name, float baseLength, float height, glm::vec3 color);
}