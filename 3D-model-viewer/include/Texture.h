#include <GL/glew.h>
#include <GLFW/glfw3.h>


class Texture {
private:
    GLuint textureID;
    GLint textureLocation;
    GLshort textureNum;

public:
    Texture();

    void Load( char* path, char* textureUniformName, GLuint shaderProgram, GLint textureNum );

    GLuint GetTextureId() { return textureID; }
    GLshort GetTextureNum() { return textureNum; }

};