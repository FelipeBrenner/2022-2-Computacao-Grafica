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
            if(abs(x) > mesh->xHitbox) mesh->xHitbox = abs(x);
            if(abs(y) > mesh->yHitbox) mesh->yHitbox = abs(y);
            if(abs(z) > mesh->zHitbox) mesh->zHitbox = abs(z);
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
    vector<vec3> verticesInfo;

    string token;
    while (getline(sline, token, ' ')) {

        if (token.empty()) {
            continue;
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

        vec3 verticeInfo = vec3(v, n, t);
        verticesInfo.push_back(verticeInfo);

    }
    int i = 0;
    int j = 0;
    int ignore = -1;
    int inFace = 0;

    while (i < verticesInfo.size() - 2) {

        for (vec3& verticeInfo : verticesInfo) {
            if (j > 0 and j <= ignore) {
                j++;
                continue;
            }
            face->push(verticesInfo[j].x, verticesInfo[j].y, verticesInfo[j].z);
            inFace++;
            if (inFace > 2) break;
            j++;
        }
        inFace = 0;
        ignore = j - 1;
        j = 0;
        i++;
        group->addFace(face);
        Face* face = new Face();
    }

}