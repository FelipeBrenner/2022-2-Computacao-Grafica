#pragma once
#include <string>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class Material
{
private:
    string name;
    vec3* ambient;
    vec3* diffuse;
    vec3* specular;
    float shininess;
    string texture;

public:
    Material();

    void setName(string n) {
        name = n;
    }

    string getName() {
        return name;
    }

    void setTexture(string n) {
        texture = n;
    }

    string getTexture() {
        return texture;
    }

    void setShininess(float n) {
        shininess = n;
    }

    float getShininess() {
        return shininess;
    }

    void setAmbient(vec3* n) {
        ambient = n;
    }

    vec3* getAmbient() {
        return ambient;
    }

    void setDiffuse(vec3* n) {
        diffuse = n;
    }

    vec3* getDiffuse() {
        return diffuse;
    }

    void setSpecular(vec3* n) {
        specular = n;
    }

    vec3* getSpecular() {
        return specular;
    }
};