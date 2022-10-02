#pragma once
#include "Face.h"
#include "Texture.h"
#include "Material.h"
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>

using namespace std;

class Group {
  public:
    Group();

    string name;
    vector <Face*> faces;
    GLuint vao;
    Texture* texture;
    map<string, Material*> materials;

    int addMaterial(string name, Material* material) {
      materials[name] = material;
      return materials.size() - 1;
    }
};
