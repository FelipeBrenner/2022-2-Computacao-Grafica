#include "ObjReader.h"

Mesh* ObjReader::read(string filename) {
    Mesh* mesh = new Mesh();

    bool firstGroup = 1;
    Group* group = new Group();
    group->setName("default");
    string path, mtlName;
    float x, y, z;

    ifstream archive(filename);

    while (!archive.eof()) {
        string line;
        getline(archive, line);

        stringstream sline(line);

        string temp;
        sline >> temp;

        if (temp == "mtllib") {
            sline >> path;
            MtlReader::read(mesh, path);
        }
        else if (temp == "v") {
            sline >> x >> y >> z;
            mesh->addVertice(new glm::vec3(x, y, z));
        }
        else if (temp == "vt") {
            sline >> x >> y;
            mesh->addTexture(new glm::vec2(x, y));
        }
        else if (temp == "vn") {
            sline >> x >> y;
            mesh->addNormal(new glm::vec3(x, y, z));
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
            sline >> mtlName;
            group->setMaterial(mtlName);
        }
    }

    archive.close();

    mesh->addGroup(group);
    return mesh;
}

void ObjReader::face(Group* group, stringstream& sline) {
    Face* face = new Face();

    string token;
    int i = 0;
    while (getline(sline, token, ' ')) {

        if (token.empty()) {
            continue;
        }

        if (i++ > 2) {
            Face* face2 = face;
            face = new Face();
            face->push(face2->getVertices()[0], face2->getNormais()[0], face2->getTextures()[0]);
            face->push(face2->getVertices()[1], face2->getNormais()[1], face2->getTextures()[1]);
            group->addFace(face2);
        }

        stringstream stoken(token);

        string aux;
        getline(stoken, aux, '/');
        int v;
        if (aux.empty()) v = 0;
        else v = stoi(aux);

        getline(stoken, aux, '/');
        int t;
        if (aux.empty()) t = 0;
        else t = stoi(aux);

        getline(stoken, aux, '/');
        int n;
        if (aux.empty()) n = 0;
        else n = stoi(aux);

        face->push(v, n, t);


    }

    group->addFace(face);
}
