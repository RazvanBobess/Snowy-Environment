#version 330

layout(location = 0) out vec4 out_color;

in vec2 frag_texcoord;
in vec3 frag_color;
in vec3 frag_position;
in vec3 frag_normal;

uniform int isLeaves;
uniform int isTrunk;
uniform int isSnow;
uniform int useTexture;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;

void main() {
    vec4 final_color = vec4(frag_color, 1.0);

    if (useTexture == 1) {
        if (isSnow == 1) {
            vec4 snow_texture_color = texture(texture1, frag_texcoord);
            final_color = snow_texture_color;
        } else if (isTrunk == 1) {
            vec4 bark_texture_color = texture(texture2, frag_texcoord);
            final_color = bark_texture_color;
        } else if (isLeaves == 1) {
            vec4 leaves_texture_color = texture(texture3, frag_texcoord);
            final_color = leaves_texture_color;
        }
    }

    out_color = final_color;
}