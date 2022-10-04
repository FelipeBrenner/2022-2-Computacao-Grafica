#pragma once
#include "Face.h"
#include "Texture.h"
#include "Material.h"
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

class Group {
  public:
    Group();

    string name;
    GLuint vao;
    vector <Face*> faces;
    string material;
    int numVertices;
};
