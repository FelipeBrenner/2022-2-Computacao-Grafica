
#include "Face.h"
Face::Face() {}


int Face::addVertice(int v) {
    vertices.push_back(v);
    return vertices.size() - 1;
}

void Face::push(int v, int n, int t) {
    vertices.push_back(v);
    normais.push_back(n);
    textures.push_back(t);
}
