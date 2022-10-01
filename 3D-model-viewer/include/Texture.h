#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

using namespace std;

class Texture {
    public:
    Texture();

    void Load( char* path, char* textureUniformName, GLuint shaderProgram, GLint textureNum );

    GLuint textureID;
    GLint textureLocation;
    GLshort textureNum;
    void loadImage(char* path);
};
