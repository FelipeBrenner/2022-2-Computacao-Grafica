#pragma once
#include <vector>
#include <map>
#include "Group.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Material.h"

using namespace std;
using namespace glm;

class Mesh {

private:
    vector<Group*> groups;
    vector<vec3*> vertices;
    vector<vec2*> textures;
    vector<vec3*> normais;
    map<string, Material*> materials;

public:
    Mesh();
    vec3* vertice(int id);
    vec2* texture(int id);
    vec3* normal(int id);
    int addVertice(vec3*);
    int addTexture(vec2*);
    int addNormal(vec3*);
    int addGroup(Group*);
    int addMaterial(string name, Material* material);
    void translateModel(vec3 initialTrans);
    void scaleModel(vec3 initalScale);
    void rotateModel(float angle, vec3 initalRotation);
    glm::mat4 model;
    
    string objectName;
    float x, y, z, scale;
    
    vector<Group*> getGroups() {
        return groups;
    }

    Material* getMaterial(string name) {
        return materials[name];
    }
};

