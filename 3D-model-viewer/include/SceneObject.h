#pragma once
#include <string>
#include <glm/glm.hpp>
#include <vector>
#include <map>

using namespace std;
using namespace glm;

class SceneObject {
    public:
        SceneObject();
        string path;
        int objId;
        vec3 initalEscale;
        vec3 initalTrans;
        vec3 initalRot;
};
