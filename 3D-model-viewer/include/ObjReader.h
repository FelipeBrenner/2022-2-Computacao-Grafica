#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "Mesh.h"
#include "Group.h"
#include "MtlReader.h"

using namespace std;

class ObjReader
{
public:
    static Mesh* read(string filename);

    static void material(Mesh* mesh, stringstream& sline);
    static void vertice(Mesh* mesh, stringstream& sline);
    static void normal(Mesh* mesh, stringstream& sline);
    static void texture(Mesh* mesh, stringstream& sline);
    static void face(Group* group, stringstream& sline);
    static void usemtl(Group* group, stringstream& sline);
};


