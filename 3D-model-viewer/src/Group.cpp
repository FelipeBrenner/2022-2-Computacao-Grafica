#include "Group.h"

Group::Group() {}

int Group::addFace(Face* face) {
    faces.push_back(face);
    return faces.size() - 1;
}
