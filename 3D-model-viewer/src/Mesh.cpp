#include "Mesh.h"
 
Mesh::Mesh() {
    model = mat4(1.0f);
    x = 0;
    y = 0;
    z = 0;
}

glm::vec3* Mesh::vertice(int id) {
    return vertices[id];
}

glm::vec2* Mesh::texture(int id) {
    return textures[id];
}

glm::vec3* Mesh::normal(int id) {
    return normais[id];
}

int Mesh::addVertice(vec3* vec)
{
    vertices.push_back(vec);
    return vertices.size() - 1;
}

int Mesh::addTexture(vec2* vec)
{
    textures.push_back(vec);
    return textures.size() - 1;
}

int Mesh::addNormal(vec3* vec)
{
    normais.push_back(vec);
    return normais.size() - 1;
}

int Mesh::addGroup(Group* group) {
    groups.push_back(group);
    return groups.size() - 1;
}

int Mesh::addMaterial(string name, Material* material) {
    materials[name] = material;
    return materials.size() - 1;
}

void Mesh::translateModel(vec3 translation) {
    x += translation.x;
    y += translation.y;
    z += translation.z;
    model = glm::translate(model, translation);
}

void Mesh::scaleModel(vec3 initalScale) {
    scale = initalScale.z;
    model = glm::scale(model, initalScale);
}

void Mesh::rotateModel(float angle, vec3 initalRotation) {
    model = glm::rotate(model, angle, initalRotation);
}


