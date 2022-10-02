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
    Group(string n, Material m) {
      name = n;
      material = m;
    };

    void setMaterial(Material* material) {
        material = material;
    };

    string name;
    Material material;
    vector <Face*> faces;
    GLuint vao;
    Texture* texture;
};
