#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Mesh.h"
#include "Group.h"
#include "MtlReader.h"

using namespace std;

class ObjReader {
    public:
        static Mesh* read(string filename);

        static void face(Group* group, stringstream& sline);
};

