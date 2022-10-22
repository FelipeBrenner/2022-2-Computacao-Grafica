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
        }else if (temp == "Ka") {
            ambient(material, sline);
        }else if (temp == "Kd") {
            diffuse(material, sline);
        }else if (temp == "Ks") {
            specular(material, sline);
        }else if (temp == "Ns") {
            shininess(material, sline);
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

void MtlReader::ambient(Material* material, stringstream& sline) {
    float x, y, z;
    sline >> x >> y >> z;
    material->setAmbient(new glm::vec3(x, y, z));
}

void MtlReader::diffuse(Material* material, stringstream& sline) {
    float x, y, z;
    sline >> x >> y >> z;
    material->setDiffuse(new glm::vec3(x, y, z));
}

void MtlReader::specular(Material* material, stringstream& sline) {
    float x, y, z;
    sline >> x >> y >> z;
    material->setSpecular(new glm::vec3(x, y, z));
}

void MtlReader::shininess(Material* material, stringstream& sline) {
    float shininess;
    sline >> shininess;
    material->setShininess(shininess);
}