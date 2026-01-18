#version 330

layout(location = 0) out vec4 out_color;

in vec2 frag_texcoord;
in vec3 frag_color;
in vec3 frag_position;
in vec3 frag_normal;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform int useTexture;

uniform int isLeaves;
uniform int isTrunk;

void main() {
    if (useTexture == 1) {
        vec4 tex_color = texture(texture1, frag_texcoord);
        out_color = tex_color;
    } else if (useTexture == 2) {
        vec4 tex_color1 = texture(texture2, frag_texcoord);
        out_color = mix(tex_color1, tex_color1, 0.5);
    } else {
        out_color = vec4(frag_color, 1.0);
    }
}