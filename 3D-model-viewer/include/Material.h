#pragma once
#include <string>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class Material
{
private:

public:
    Material();

    string name;
    vec3* ambient;
    vec3* diffuse;
    vec3* specular;
    float shininess;
    string texture;
};