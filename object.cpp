#include "lab_m1/tema3/object.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

void createCube(glm::vec3 pos,
    float w, float h, float d,
    glm::vec3 color,
    std::vector<VertexFormat>& vertices,
    std::vector<unsigned int>& indices) {
        unsigned int start_index = vertices.size();

        vertices.push_back(VertexFormat(glm::vec3(pos.x, pos.y, pos.z), color));
        vertices.push_back(VertexFormat(glm::vec3(pos.x + w, pos.y, pos.z), color));
        vertices.push_back(VertexFormat(glm::vec3(pos.x + w, pos.y + h, pos.z), color));
        vertices.push_back(VertexFormat(glm::vec3(pos.x, pos.y + h, pos.z), color));

        vertices.push_back(VertexFormat(glm::vec3(pos.x, pos.y, pos.z - d), color));
        vertices.push_back(VertexFormat(glm::vec3(pos.x + w, pos.y, pos.z - d), color));
        vertices.push_back(VertexFormat(glm::vec3(pos.x + w, pos.y + h, pos.z - d), color));
        vertices.push_back(VertexFormat(glm::vec3(pos.x, pos.y + h, pos.z - d), color));

        unsigned int cube_indices[] = {
            0,1,2, 0,2,3,
            4,6,5, 4,7,6,
            4,5,1, 4,1,0,
            3,2,6, 3,6,7,
            1,5,6, 1,6,2,
            4,0,3, 4,3,7
        };

        for (unsigned int i : cube_indices) {
            indices.push_back(start_index + i);
        }
    }

void createCylinder1(glm::vec3 pos, 
    float r, float d, float seg,
    glm::vec3 color,
    std::vector<VertexFormat>& vertices,
    std::vector<unsigned int>& indices) {
        unsigned int start_index = vertices.size();

        vertices.push_back(VertexFormat(glm::vec3(pos.x, pos.y, pos.z), color));
        vertices.push_back(VertexFormat(glm::vec3(pos.x, pos.y, pos.z - d), color));

        for (int i = 0; i <= seg; i++) {
            float theta = i * 2.f * M_PI / seg;
            float cx = pos.x + r * cos(theta);
            float cy = pos.y + r * sin(theta);

            vertices.push_back(VertexFormat(glm::vec3(cx, cy, pos.z), color));
            vertices.push_back(VertexFormat(glm::vec3(cx, cy, pos.z - d), color));
        }

        for (int i = 0; i < seg; i++) {
            unsigned int front1 = start_index + 2 + i * 2;
            unsigned int front2 = front1 + 2;
            unsigned int back1 = front1 + 1;
            unsigned int back2 = back1 + 2;

            indices.insert(indices.end(), {
                start_index, front1, front2,
                start_index + 1, back2, back1,
                front1, back1, back2,
                front1, back2, front2
            });
        }
    }

void createCylinder3(glm::vec3 pos,
    float r, float h, float seg,
    glm::vec3 color,
    std::vector<VertexFormat>& vertices,
    std::vector<unsigned int>& indices) {
        unsigned int start_index = vertices.size();

        vertices.push_back(VertexFormat(glm::vec3(pos.x, pos.y, pos.z), color));
        vertices.push_back(VertexFormat(glm::vec3(pos.x, pos.y + h, pos.z), color));

        for (int i = 0; i <= seg; i++) {
            float theta = i * 2.f * M_PI / seg;
            float cx = pos.x + r * cos(theta);
            float cz = pos.z + r * sin(theta);

            vertices.push_back(VertexFormat(glm::vec3(cx, pos.y, cz), color));
            vertices.push_back(VertexFormat(glm::vec3(cx, pos.y + h, cz), color));
        }

        for (int i = 0; i < seg; i++) {
            unsigned int front1 = start_index + 2 + i * 2;
            unsigned int front2 = front1 + 2;
            unsigned int back1 = front1 + 1;
            unsigned int back2 = back1 + 2;

            indices.insert(indices.end(), {
                start_index, front1, front2,
                start_index + 1, back2, back1,
                front1, back1, back2,
                front1, back2, front2
            });
        }        
    }


void createCylinder2(glm::vec3 pos,
    float r, float d, float seg,
    glm::vec3 color,
    std::vector<VertexFormat>& vertices,
    std::vector<unsigned int>& indices) {
        unsigned int start_index = vertices.size();

        vertices.push_back(VertexFormat(glm::vec3(pos.x, pos.y, pos.z), color));
        vertices.push_back(VertexFormat(glm::vec3(pos.x - d, pos.y, pos.z), color));

        for (int i = 0; i <= seg; i++) {
            float theta = i * 2.f * M_PI / seg;
            float cy = pos.y + r * cos(theta);
            float cz = pos.z + r * sin(theta);

            vertices.push_back(VertexFormat(glm::vec3(pos.x, cy, cz), color));
            vertices.push_back(VertexFormat(glm::vec3(pos.x - d, cy, cz), color));
        }

        for (int i = 0; i < seg; i++) {
            unsigned int front1 = start_index + 2 + i * 2;
            unsigned int front2 = front1 + 2;
            unsigned int back1 = front1 + 1;
            unsigned int back2 = back1 + 2;

            indices.insert(indices.end(), {
                start_index, front1, front2,
                start_index + 1, back2, back1,
                front1, back1, back2,
                front1, back2, front2
            });
        }
    }

Mesh* object3D::CreateTree
    (const std::string& name, 
    glm::vec3 center) 
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    createCylinder3(center, 0.2f, 5.f, 20, BROWN_COLOR, vertices, indices);

    Mesh* tree = new Mesh(name);
    tree->InitFromData(vertices, indices);
    return tree;
}

Mesh* object3D::CreateLeaves(const std::string& name, glm::vec3 center) 
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    createCube(center + glm::vec3(-1.5f, 2.f, 0.5f), 3.f, 0.2f, 1.f, DARK_GREEN_COLOR, vertices, indices);
    createCube(center + glm::vec3(-1.35f, 2.4f, 0.47f), 2.7f, 0.3f, 0.94f, DARK_GREEN_COLOR, vertices, indices);
    createCube(center + glm::vec3(-1.2f, 2.9f, 0.44f), 2.4f, 0.35f, 0.88f, DARK_GREEN_COLOR, vertices, indices);
    createCube(center + glm::vec3(-1.05f, 3.4f, 0.425f), 2.1f, 0.38f, 0.85f, DARK_GREEN_COLOR, vertices, indices);
    createCube(center + glm::vec3(-0.7f, 3.9f, 0.41f), 1.4f, 0.4f, 0.82f, DARK_GREEN_COLOR, vertices, indices);
    createCube(center + glm::vec3(-0.25f, 4.5f, 0.4f), 0.5f, 0.5f, 0.8f, DARK_GREEN_COLOR, vertices, indices);

    Mesh* leaves = new Mesh(name);
    leaves->InitFromData(vertices, indices);
    return leaves;
}

Mesh* object3D::CreateTerrain(const std::string& name, glm::vec3 center) 
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    createCube(center + glm::vec3(-50.f, -0.1f, 50.f), 100.f, 0.2f, 100.f, LIGHT_GRAY_COLOR, vertices, indices);

    Mesh* terrain = new Mesh(name);
    terrain->InitFromData(vertices, indices);
    return terrain;
}


void AddPart(std::vector<VertexFormat>& vertices, std::vector<unsigned int>& indices,
    std::pair<std::vector<unsigned int>, std::vector<VertexFormat>> part, glm::vec3 offset)
{
    unsigned int currentVertexCount = (unsigned int)vertices.size();

    for (unsigned int idx : part.first) {
        indices.push_back(idx + currentVertexCount);
    }

    for (VertexFormat v : part.second) {
        v.position += offset;
        vertices.push_back(v);
    }
}

std::pair<std::vector<unsigned int>, std::vector<VertexFormat>>
CreateBox(float width, float height, float depth, glm::vec3 color)
{
    float w = width / 2.0f;
    float h = height;
    float d = depth / 2.0f;

    std::vector<VertexFormat> vertices = {
        // Back face
        VertexFormat(glm::vec3(-w, 0, -d), color, glm::vec3(0,1,0),glm::vec2(0.0f, 0.0f)),
        VertexFormat(glm::vec3(w, 0, -d), color, glm::vec3(0,1,0),glm::vec2(1.0f, 0.0f)),
        VertexFormat(glm::vec3(w, h, -d), color, glm::vec3(0,1,0),glm::vec2(1.0f, 1.0f)),
        VertexFormat(glm::vec3(-w, h, -d), color, glm::vec3(0,1,0),glm::vec2(0.0f, 1.0f)),

        // Front face
        VertexFormat(glm::vec3(-w, 0, d), color, glm::vec3(0,1,0),glm::vec2(0.0f, 0.0f)),
        VertexFormat(glm::vec3(w, 0, d), color, glm::vec3(0,1,0),glm::vec2(1.0f, 0.0f)),
        VertexFormat(glm::vec3(w, h, d), color, glm::vec3(0,1,0),glm::vec2(1.0f, 1.0f)),
        VertexFormat(glm::vec3(-w, h, d), color, glm::vec3(0,1,0),glm::vec2(0.0f, 1.0f)),

        // Left face
        VertexFormat(glm::vec3(-w, 0, -d), color, glm::vec3(0,1,0),glm::vec2(0.0f, 0.0f)),
        VertexFormat(glm::vec3(-w, 0,  d), color, glm::vec3(0,1,0),glm::vec2(1.0f, 0.0f)),
        VertexFormat(glm::vec3(-w, h,  d), color, glm::vec3(0,1,0),glm::vec2(1.0f, 1.0f)),
        VertexFormat(glm::vec3(-w, h, -d), color, glm::vec3(0,1,0),glm::vec2(0.0f, 1.0f)),

        // Right face
        VertexFormat(glm::vec3(w, 0, -d), color, glm::vec3(0,1,0),glm::vec2(0.0f, 0.0f)),
        VertexFormat(glm::vec3(w, 0,  d), color, glm::vec3(0,1,0),glm::vec2(1.0f, 0.0f)),
        VertexFormat(glm::vec3(w, h,  d), color, glm::vec3(0,1,0),glm::vec2(1.0f, 1.0f)),
        VertexFormat(glm::vec3(w, h, -d), color, glm::vec3(0,1,0),glm::vec2(0.0f, 1.0f)),

        // Top face
        VertexFormat(glm::vec3(-w, h, -d), color, glm::vec3(0,1,0),glm::vec2(0.0f, 0.0f)),
        VertexFormat(glm::vec3(w, h, -d), color, glm::vec3(0,1,0),glm::vec2(1.0f, 0.0f)),
        VertexFormat(glm::vec3(w, h,  d), color, glm::vec3(0,1,0),glm::vec2(1.0f, 1.0f)),
        VertexFormat(glm::vec3(-w, h,  d), color, glm::vec3(0,1,0),glm::vec2(0.0f, 1.0f)),

        // Bottom face
        VertexFormat(glm::vec3(-w, 0, -d), color, glm::vec3(0,1,0),glm::vec2(0.0f, 0.0f)),
        VertexFormat(glm::vec3(w, 0, -d), color, glm::vec3(0,1,0),glm::vec2(1.0f, 0.0f)),
        VertexFormat(glm::vec3(w, 0,  d), color, glm::vec3(0,1,0),glm::vec2(1.0f, 1.0f)),
        VertexFormat(glm::vec3(-w, 0,  d), color, glm::vec3(0,1,0),glm::vec2(0.0f, 1.0f))
    };

    std::vector<unsigned int> indices;
    for (int i = 0; i < 6; i++) {
        int offset = i * 4;
        indices.push_back(offset + 0); indices.push_back(offset + 1); indices.push_back(offset + 2);
        indices.push_back(offset + 0); indices.push_back(offset + 2); indices.push_back(offset + 3);
    }

    return { indices, vertices };
}

std::pair<std::vector<unsigned int>, std::vector<VertexFormat>>
CreateConePart(float radius, float height, int segments, glm::vec3 color)
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    vertices.emplace_back(
        glm::vec3(0, height, 0),
        color,
        glm::vec3(0, 1, 0),
        glm::vec2(0.5f, 1.0f)
    );

    vertices.emplace_back(
        glm::vec3(0, 0, 0),
        color,
        glm::vec3(0, -1, 0),
        glm::vec2(0.5f, 0.5f)
    );

    int apexIndex = 0;
    int centerIndex = 1;
    int baseStart = 2;

    for (int i = 0; i < segments; i++) {
        float angle = 2.0f * M_PI * i / segments;
        float x = radius * cos(angle);
        float z = radius * sin(angle);

        glm::vec3 sideNormal = glm::normalize(glm::vec3(x, radius / height, z));

        float u = (float)i / segments;
        float v = 0.0f;

        vertices.emplace_back(
            glm::vec3(x, 0, z),
            color,
            sideNormal,
            glm::vec2(u, v)
        );
    }

    for (int i = 0; i < segments; i++) {
        int curr = baseStart + i;
        int next = baseStart + (i + 1) % segments;

        indices.push_back(apexIndex);
        indices.push_back(curr);
        indices.push_back(next);
    }

    for (int i = 0; i < segments; i++) {
        int curr = baseStart + i;
        int next = baseStart + (i + 1) % segments;

        indices.push_back(centerIndex);
        indices.push_back(next);
        indices.push_back(curr);
    }

    return { indices, vertices };
}


Mesh* object3D::CreateObservationTower(
    std::unordered_map<std::string, Mesh*>& meshes,
    const char* name)
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    glm::vec3 color(0.4f, 0.25f, 0.1f);

    float pillarHeight = 12.0f;
    float pillarSize = 0.3f;
    float platformHeight = pillarHeight * 0.75f;
    float platformSize = 4.5f;
    float platformThickness = 1.0f;

    float halfPlatform = platformSize / 2.0f;

    auto pillar = CreateBox(
        pillarSize,
        pillarHeight,
        pillarSize,
        color
    );

    AddPart(vertices, indices, pillar, glm::vec3(-halfPlatform, 0, -halfPlatform));
    AddPart(vertices, indices, pillar, glm::vec3(halfPlatform, 0, -halfPlatform));
    AddPart(vertices, indices, pillar, glm::vec3(-halfPlatform, 0, halfPlatform));
    AddPart(vertices, indices, pillar, glm::vec3(halfPlatform, 0, halfPlatform));

    auto platform = CreateBox(
        platformSize,
        platformThickness,
        platformSize,
        color
    );

    AddPart(vertices, indices, platform,
        glm::vec3(0, platformHeight, 0));

    auto roof = CreateConePart(
        platformSize * 0.9f,
        2.5f,
        24,
        color
    );


    AddPart(vertices, indices, roof,
        glm::vec3(0, pillarHeight, 0));

    Mesh* tower = new Mesh(name);
    tower->InitFromData(vertices, indices);

    return tower;
}

Mesh* object3D::CreatePyramid
    (std::unordered_map<std::string, 
    Mesh*>& meshes, 
    const char* name, 
    float baseLength, 
    float height, 
    glm::vec3 color) 
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    float halfBase = baseLength * 0.5f;

    vertices.push_back(VertexFormat(glm::vec3(-halfBase, 0, -halfBase), color));
    vertices.push_back(VertexFormat(glm::vec3(halfBase, 0, -halfBase), color));
    vertices.push_back(VertexFormat(glm::vec3(halfBase, 0, halfBase), color));
    vertices.push_back(VertexFormat(glm::vec3(-halfBase, 0, halfBase), color));
    vertices.push_back(VertexFormat(glm::vec3(0, height, 0), color));

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(4);

    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(4);

    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(4);

    indices.push_back(3);
    indices.push_back(0);
    indices.push_back(4);

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(3);

    Mesh* pyramid = new Mesh(name);

    pyramid->InitFromData(vertices, indices);

    return pyramid;
}