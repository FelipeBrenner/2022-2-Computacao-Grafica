#include "ObjReader.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

Mesh* ObjReader::read(string filename)
{
    Mesh* mesh = new Mesh();

    int firstGroup = 1;
    Group* group = new Group();
    group->setName("default");

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

        if (temp == "mtllib") {
            material(mesh, sline);
        } else if (temp == "v") {
            vertice(mesh, sline);
        }
        else if (temp == "vn") {
            normal(mesh, sline);
        }
        else if (temp == "vt") {
            texture(mesh, sline);
        }
        else if (temp == "f") {
            face(group, sline);
        }
        else if (temp == "g") {
            if (firstGroup == 1) {
                firstGroup = 0;
            }
            else {
                mesh->addGroup(group);
                group = new Group();
            }

            string name;
            sline >> name;
            group->setName(name);
        }
        else if (temp == "usemtl") {
            usemtl(group, sline);
        }

        // cout << endl;
    }

    arq.close();

    mesh->addGroup(group);
    return mesh;
}


void ObjReader::material(Mesh* mesh, stringstream& sline) {
    string path;
    sline >> path;
    MtlReader::read(mesh, path);
}

void ObjReader::vertice(Mesh* mesh, stringstream &sline) {
    float x, y, z;
    sline >> x >> y >> z;
    // cout << "  Resultado: vec3(" << x << ", " << y << ", " << z << ")" << endl;
    mesh->addVertice(new glm::vec3(x, y, z));
}

void ObjReader::normal(Mesh* mesh, stringstream& sline) {
    float x, y, z;
    sline >> x >> y >> z;
    // cout << "  Resultado: vec3(" << x << ", " << y << ", " << z << ")" << endl;
    mesh->addNormal(new glm::vec3(x, y, z));
}

void ObjReader::texture(Mesh* mesh, stringstream& sline) {
    float x, y;
    sline >> x >> y;
    // cout << "  Resultado: vec2(" << x << ", " << y << ")" << endl;
    mesh->addTexture(new glm::vec2(x, y));
}

int getNextTokenValue(stringstream& stoken) {
    string temp;
    getline(stoken, temp, '/');
    return temp.empty() ? 0 : stoi(temp);
}

void ObjReader::face(Group* group, stringstream& sline) {
    Face* face = new Face();

    string token;
    while (getline(sline, token, ' ')) {

        if (token.empty()) {
            continue;
        }

        stringstream stoken(token);

        int v = getNextTokenValue(stoken);
        int t = getNextTokenValue(stoken);
        int n = getNextTokenValue(stoken);

        // cout << "  Resultado de " << token << ": " << endl;
        // cout << "   - Vertice: " << v << endl;
        // cout << "   - Textura: " << t << endl;
        // cout << "   - Normal:  " << n << endl;

        face->push(v, n, t);
    }

    group->addFace(face);
}

void ObjReader::usemtl(Group* group, stringstream& sline) {
    string name;
    sline >> name;
    group->setMaterial(name);
}
