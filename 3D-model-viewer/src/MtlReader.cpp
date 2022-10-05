#include "MtlReader.h"

void MtlReader::read(Mesh* mesh, string filename) {
    bool firstMtl = 1;

    Material* material = new Material();

    ifstream archive(filename);

    while (!archive.eof()) {
        string line;
        getline(archive, line);

        stringstream sline(line);

        string temp;
        sline >> temp;
        if (temp == "newmtl") {
            if (firstMtl == 1) {
                firstMtl = 0;
            }
            else {
                mesh->addMaterial(material->getName(), material);
                material = new Material();
            }

            name(material, sline);
        }else if (temp == "map_Kd") {
            texture(material, sline);
        }

    }
    archive.close();
    mesh->addMaterial(material->getName(), material);
}

void MtlReader::name(Material* material, stringstream& sline) {
    string name;
    sline >> name;
    material->setName(name);
}

void MtlReader::texture(Material* material, stringstream& sline) {
    string texture;
    sline >> texture;
    material->setTexture(texture);
}
