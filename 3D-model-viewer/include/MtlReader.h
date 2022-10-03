#pragma once
#include <string>
#include "Material.h"
#include "Mesh.h"

using namespace std;

class MtlReader {
    public:
        static void read(Mesh* mesh, string filename);

        static void name(Material* material, stringstream& sline);
        static void texture(Material* material, stringstream& sline);
};
