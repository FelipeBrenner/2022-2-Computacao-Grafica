#include "Texture.h"
#include "stb_image.h"

Texture::Texture() {}

void Texture::Load(char* path, char* textureUniformName, GLuint shaderProgram, GLint textureNum ) {
    this->textureNum = textureNum;

    glGenTextures( 1, &textureID );

    int width, height, numComp;;
    unsigned char *image;

    textureLocation = glGetUniformLocation( shaderProgram, textureUniformName );

    glActiveTexture( GL_TEXTURE0 + this->textureNum );
    glBindTexture( GL_TEXTURE_2D, textureID );


    image = stbi_load(path, &width, &height, &numComp, 4);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glUniform1i( textureLocation, this->textureNum );

    glBindTexture( GL_TEXTURE_2D, 0 );
}
