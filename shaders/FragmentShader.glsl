#version 330

layout(location = 0) out vec4 out_color;

in vec2 frag_texcoord;
in vec3 frag_color;
in vec3 frag_position;
in vec3 frag_normal;

uniform sampler2D texture1;
uniform int useTexture;

void main() {
    if (useTexture == 1) {
        out_color = texture(texture1, frag_texcoord);
    } else {
        out_color = vec4(frag_color, 1.0);
    }
}