#include "MtlReader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void MtlReader::read(Mesh* mesh, string filename)
{
    int firstMtl = 1;
    Material* material = new Material();

    ifstream arq(filename);

    if (!arq) {
        exit(EXIT_FAILURE);
    }

    while (!arq.eof()) {
        string line;
        getline(arq, line);

        stringstream sline(line);

        string temp;
        sline >> temp;

        if (temp.empty() || temp == "#") {
            continue;
        }

        if (temp == "newmtl") {
            if (firstMtl == 1) {
                firstMtl = 0;
            }
            else {
                mesh->addMaterial(material->name, material);
                material = new Material();
            }

            name(material, sline);
        }
        else if (temp == "map_Kd") {
            texture(material, sline);
        }
    }

    arq.close();

    mesh->addMaterial(material->name, material);
}

void MtlReader::name(Material* material, stringstream& sline) {
    string name;
    sline >> name;
    material->name = name;
}

void MtlReader::texture(Material* material, stringstream& sline) {
    string texture;
    sline >> texture;
    material->texture = texture;
}