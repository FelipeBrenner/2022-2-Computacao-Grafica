#include "SceneReader.h"
#include "SceneObject.h"

SceneReader::SceneReader() {}

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
        else if (identifier == "translation") {
            string transx, transy, transz;
            sline >> transx >> transy >> transz;
            sceneObject->initalTrans = vec3(stof(transx), stof(transy), stof(transz));
        }
        else if (identifier == "rotation") {
            string rotx, roty, rotz;
            sline >> rotx >> roty >> rotz;
            sceneObject->initalRot = vec3(stof(rotx), stof(roty), stof(rotz));
        }
        else if (identifier == "scale") {
            string scalex, scaley, scalez;
            sline >> scalex >> scaley >> scalez;
            sceneObject->initalEscale = vec3(stof(scalex), stof(scaley), stof(scalez));
        }
        else if (identifier == "eliminable") {

        }
    }

    sceneObject->objId = ++objCount;
    sceneObjects.push_back(sceneObject);
    archive.close();

}

