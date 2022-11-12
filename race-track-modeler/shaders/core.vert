#version 410 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 aNormal;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    vec4 pos = model * vec4(vPosition, 1.0);

    gl_Position = projection * view * pos;

    TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
    Normal = mat3(transpose(inverse(model))) * aNormal;
    //Normal = normalize(vec3(model * vec4(aNormal, 0.0)));//This example was on lernopengl
    FragPos = vec3(pos);
}
