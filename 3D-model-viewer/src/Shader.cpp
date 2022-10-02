#include "Shader.h"

Shader::Shader() {
	textureQtd = 0;
	
		/* these are the strings of code for the shaders
	the vertex shader positions each vertex point */
	/* these are the strings of code for the shaders
	the vertex shader positions each vertex point */
	const char* vertex_shader =
		"#version 410\n"
		"layout(location=0) in vec3 vp;"
		"layout(location=1) in vec2 aTexCoord;"
		"uniform mat4 view;"
		"uniform mat4 projection;"
		"out vec2 TexCoord;"
		"void main () {"
		"   TexCoord = aTexCoord;"
		"	gl_Position = projection * view * vec4 (vp, 1.0);"
		"}";

	/* the fragment shader colours each fragment (pixel-sized area of the
	triangle) */
	const char* fragment_shader =
		"#version 410\n"
		"in vec2 TexCoord;"
		"uniform sampler2D texture1;"
		"out vec4 frag_color;"
		"void main () {"
		//"	frag_color = vec4 (color, 1.0);"
		"	frag_color = texture(texture1, TexCoord);"
		"}";

	/* GL shader objects for vertex and fragment shader [components] */
	GLuint vs, fs;

	/* here we copy the shader strings into GL shaders, and compile them. we then
	create an executable shader 'program' and attach both of the compiled shaders.
	we link this, which matches the outputs of the vertex shader to the inputs of
	the fragment shader, etc. and it is then ready to use */
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	glUseProgram(shader_programme);
}

void Shader::useTexture( string textureName )
{
	glActiveTexture( GL_TEXTURE0 + textures[textureName].textureNum );
	glBindTexture( GL_TEXTURE_2D, textures[textureName].textureID );
}

void Shader::loadTexture( char* path, char* textureUniformName, string textureName )
{
	Texture tmpTexture;
	tmpTexture.Load( path, textureUniformName, shader_programme, textureQtd );
	textures[textureName] = tmpTexture;
	textureQtd += 1;
}

void Shader::setUniformMatrix4fv(const string& name, glm::mat4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(shader_programme, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setUniformMatrix4fvFloat(const string& name, float* matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(shader_programme, name.c_str()), 1, GL_FALSE, matrix);
}