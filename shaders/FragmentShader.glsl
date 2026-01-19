#version 330

layout(location = 0) out vec4 out_color;

in vec2 frag_texcoord;
in vec3 frag_color;
in vec3 frag_position;
in vec3 frag_normal;

uniform int useTexture;
uniform sampler2D texture1;

uniform vec3 fogColor;
uniform float fogStart;
uniform float fogEnd;
uniform vec3 cameraPos;

void main() {
    vec4 final_color = vec4(frag_color, 1.0);

    if (useTexture == 1) {
        vec4 texture_color = texture2D(texture1, frag_texcoord);
        final_color *= texture_color;
    }

    float d = length(frag_position - cameraPos);
    float fogFactor = clamp(d / (fogEnd - fogStart), 0.0, 1.0);

    vec3 color = mix(final_color.rgb, fogColor, fogFactor);

    out_color = vec4(color, final_color.a);
}