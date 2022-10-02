#include "MtlReader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void MtlReader::read(Group* group, string filename)
{
    int firstMtl = 1;
    Material* material = new Material();

    ifstream arq(filename);

    // cout << "Lendo arquivo: " << filename << endl;

    if (!arq) {
        // cout << "- Arquivo de objeto nao encontrado" << endl;
        exit(EXIT_FAILURE);
    }

    // cout << endl;

    while (!arq.eof()) {
        string line;
        getline(arq, line);

        stringstream sline(line);

        // l� tipo de elemento
        string temp;
        sline >> temp;

        if (temp.empty() || temp == "#") {
            continue;
        }

        // cout << "Linha lida: " << line << endl;
        // cout << "- Tipo: " << temp << endl;

        if (temp == "newmtl") {
            if (firstMtl == 1) {
                firstMtl = 0;
            }
            else {
                //group->setMaterial(material->getName());
                group->setMaterial(material);
                Material* material = new Material();
            }

            name(material, sline);
        }
        else if (temp == "Ka") {
            ambient(material, sline);
        }
        else if (temp == "Kd") {
            diffuse(material, sline);
        }
        else if (temp == "Ks") {
            specular(material, sline);
        }
        else if (temp == "Ns") {
            shininess(material, sline);
        }
        else if (temp == "map_Kd") {
            texture(material, sline);
        }

        // cout << endl;
    }

    arq.close();

    group->setMaterial(material);


    //group->setMaterial(material->getName());
}

void MtlReader::name(Material* material, stringstream& sline) {
    string name;
    sline >> name;
    material->setName(name);
}

void MtlReader::ambient(Material* material, stringstream& sline) {
    float x, y, z;
    sline >> x >> y >> z;
    // cout << "  Resultado: vec3(" << x << ", " << y << ", " << z << ")" << endl;
    material->setAmbient(new glm::vec3(x, y, z));
}

void MtlReader::diffuse(Material* material, stringstream& sline) {
    float x, y, z;
    sline >> x >> y >> z;
    // cout << "  Resultado: vec3(" << x << ", " << y << ", " << z << ")" << endl;
    material->setDiffuse(new glm::vec3(x, y, z));
}

void MtlReader::specular(Material* material, stringstream& sline) {
    float x, y, z;
    sline >> x >> y >> z;
    // cout << "  Resultado: vec3(" << x << ", " << y << ", " << z << ")" << endl;
    material->setSpecular(new glm::vec3(x, y, z));
}

void MtlReader::shininess(Material* material, stringstream& sline) {
    float shininess;
    sline >> shininess;
    material->setShininess(shininess);
}

void MtlReader::texture(Material* material, stringstream& sline) {
    string texture;
    sline >> texture;
    material->setTexture(texture);
}