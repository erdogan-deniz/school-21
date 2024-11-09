#extension GL_EXT_gpu_shader4 : require
attribute vec3 aPos;
attribute vec2 aTexCoord;
attribute vec3 aNormal;

flat varying  vec3 NormalFlat;
varying  vec3 FragPos;
varying  vec3 NormalSmooth;
varying  vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 it_model;

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0));
    NormalFlat = NormalSmooth = mat3(it_model[0].xyz, it_model[1].xyz, it_model[2].xyz) * aNormal;
    TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);

    gl_Position = projection * view * vec4(FragPos, 1.0);
}
