#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Material.h"
#include "Mesh.h"

using namespace std;

class MtlReader {
public:
    static void read(Mesh* mesh, string filename);

    static void name(Material* material, stringstream& sline);
    static void ambient(Material* material, stringstream& sline);
    static void diffuse(Material* material, stringstream& sline);
    static void specular(Material* material, stringstream& sline);
    static void shininess(Material* material, stringstream& sline);
    static void texture(Material* material, stringstream& sline);
};

