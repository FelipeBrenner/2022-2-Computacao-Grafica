#include "Shader.h"

void Shader::UseTexture( std::string textureName ) {
	glBindTexture( GL_TEXTURE_2D, textures[textureName].GetTextureId() );
}

void Shader::LoadTexture( char* path, char* textureUniformName, std::string textureName ) {
	Texture tempTexture;
	tempTexture.Load( path, textureUniformName, program, textureQtd );
	textures[textureName] = tempTexture;
	textureQtd += 1;
}

void Shader::setMatrix4fv(const std::string& name, glm::mat4& matrix) {
	glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setVec3(const std::string& name, const glm::vec3& vec3) {
	glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, glm::value_ptr(vec3));
}

void Shader::setUniformMatrix4fvFloat(const std::string& name, float* matrix) {
	glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, matrix);
}

void Shader::setFloat(const std::string& name, float f)
{
	glUniform1f(glGetUniformLocation(program, name.c_str()), f);
}