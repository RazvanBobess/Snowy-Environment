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

    createCylinder3(center, 0.5f, 5.f, 20, BROWN_COLOR, vertices, indices);
    createCube(center + glm::vec3(-1.2f, 2.f, 0.5f), 2.4f, 0.4f, 1.f, GREEN_COLOR, vertices, indices);

    Mesh* tree = new Mesh(name);
    tree->InitFromData(vertices, indices);
    return tree;
}