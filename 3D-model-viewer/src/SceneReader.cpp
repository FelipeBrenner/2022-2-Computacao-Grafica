#pragma once
#include "SceneReader.h"
#include "SceneObject.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;


SceneReader::SceneReader() {
}

void SceneReader::read(string filename) {

    int objCount = 0;
    SceneObject* sceneObject = new SceneObject();
    bool firstObj = true;

    ifstream archive(filename);

    while (!archive.eof()) {
        string line;
        getline(archive, line);

        stringstream sline(line);

        string identifier;
        sline >> identifier;

        if (identifier.empty()) {
            continue;
        }

        if (identifier == "newobj") {
            if (firstObj) {
                firstObj = false;
            }
            else {
                sceneObject->objId = ++objCount;
                sceneObjects.push_back(sceneObject);
                sceneObject = new SceneObject();
            }
        }
        else if (identifier == "objpath") {
            string path;
            sline >> path;
            sceneObject->path = path;
        }
        else if (identifier == "position") {
            string transx, transy, transz, rotx, roty, rotz, scalex, scaley, scalez;
            sline >> transx >> transy >> transz >> rotx >> roty >> rotz >> scalex >> scaley >> scalez;
            sceneObject->initalTrans = vec3(stof(transx), stof(transy), stof(transz));
            sceneObject->initalRot = vec3(stof(rotx), stof(roty), stof(rotz));
            sceneObject->initalEscale = vec3(stof(scalex), stof(scaley), stof(scalez));
        }
        else if (identifier == "eliminable") {

        }
    }

    sceneObject->objId = ++objCount;
    sceneObjects.push_back(sceneObject);
    archive.close();

}

