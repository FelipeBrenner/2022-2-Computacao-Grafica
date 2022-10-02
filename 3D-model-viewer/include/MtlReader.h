#pragma once
#include <string>
#include "Material.h"
#include "Group.h"

using namespace std;

class MtlReader
{
public:
    static void read(Group* group, string filename);

    static void name(Material* material, stringstream& sline);
    static void ambient(Material* material, stringstream& sline);
    static void diffuse(Material* material, stringstream& sline);
    static void specular(Material* material, stringstream& sline);
    static void shininess(Material* material, stringstream& sline);
    static void texture(Material* material, stringstream& sline);
};
