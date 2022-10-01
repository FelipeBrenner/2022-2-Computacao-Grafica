#include "Texture.h"

Texture::Texture() {
    
}

void Texture::Load(char* path, char* textureUniformName, GLuint shaderProgram, GLint textureNum )
{
    this->textureNum = textureNum;

    glGenTextures( 1, &textureID );

    int width, height;
    unsigned char *image;

    textureLocation = glGetUniformLocation( shaderProgram, textureUniformName );

    glActiveTexture( GL_TEXTURE0 + this->textureNum );
    glBindTexture( GL_TEXTURE_2D, textureID );

    loadImage(path);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glUniform1i( textureLocation, this->textureNum );

    glBindTexture( GL_TEXTURE_2D, 0 );
}

void Texture::loadImage(char* path) {
    // load and generate the texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load("images/loud.jpeg", &width, &height, &nrChannels, 0);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}
