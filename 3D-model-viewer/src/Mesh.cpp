#include "Mesh.h"
 
Mesh::Mesh() {
    model = mat4(1.0f);
    groups.clear();
    vertices.clear();
    textures.clear();
    materials.clear();
}

glm::vec3* Mesh::vertice(int id) {
    return vertices[id];
}

glm::vec2* Mesh::texture(int id) {
    return textures[id];
}

int Mesh::addVertice(vec3* vec) {
    vertices.push_back(vec);
    return vertices.size() - 1;
}

int Mesh::addTexture(vec2* vec) {
    textures.push_back(vec);
    return textures.size() - 1;
}

int Mesh::addGroup(Group* group) {
    groups.push_back(group);
    return groups.size() - 1;
}

int Mesh::addMaterial(string name, Material* material) {
    materials[name] = material;
    return materials.size() - 1;
}

void Mesh::translateModel(vec3 initialTrans) {
    model = glm::translate(model, initialTrans);
}

void Mesh::scaleModel(vec3 initalScale) {
    model = glm::scale(model, initalScale);
}

void Mesh::rotateModel(vec3 initalRotation) {
    model = glm::rotate(model, 2.0f, initalRotation);
}


