#version 410
in vec2 TexCoord;
uniform sampler2D texture1;
out vec4 color;
void main () {
  color = texture(texture1, TexCoord);
};