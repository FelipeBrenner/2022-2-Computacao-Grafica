#include "Mesh.h"
 
Mesh::Mesh() {
    eliminated = false;
    xHitbox = 0;
    yHitbox = 0;
    zHitbox = 0;
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


