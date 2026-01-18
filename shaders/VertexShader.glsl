#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec2 frag_texcoord;
out vec3 frag_color;
out vec3 frag_position;
out vec3 frag_normal;

uniform float treeHeight;
uniform int isTrunk;

uniform int isLeaves;
uniform float time;
uniform float bendPhase;
uniform float bendFrequency;

void main() {
    vec3 modified_pos = v_position;

    if (isTrunk == 1) {
        float t = modified_pos.y / treeHeight;

        float scale = 1.0 - t;

        modified_pos.x = modified_pos.x * scale;
        modified_pos.z = modified_pos.z * scale;
    }

    if (isLeaves == 1) {
        float t = modified_pos.y / treeHeight;

        float wave = sin(time * bendFrequency + t * 0.5f + bendPhase);
        float offset;

        if (v_position.y < 2.9f) {
            offset = wave * 0.7f * t;
        } else if (v_position.y >= 2.9f && v_position.y < 3.8f) {
            offset = wave * 0.4f * t;
        } else {
            offset = wave * 0.1f * t;
        }
        modified_pos.x += offset;
    }

    vec4 world_pos_vec4 = Model * vec4(modified_pos, 1.0);
    frag_position = world_pos_vec4.xyz;

    mat3 normalMatrix = transpose(inverse(mat3(Model)));
    frag_normal = normalize(normalMatrix * v_normal);

    frag_texcoord = v_texture_coord;
    frag_color = v_color;

    gl_Position = Projection * View * world_pos_vec4;
}