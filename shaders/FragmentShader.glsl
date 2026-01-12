#version 330

layout(location = 0) out vec4 out_color;

in vec2 frag_texcoord;
in vec3 frag_color;

void main() {
    out_color = vec4(frag_color, 1.0);
}