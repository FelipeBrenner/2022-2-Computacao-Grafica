#pragma once
#include <string>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class Material {
private:
    string name;
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
};
