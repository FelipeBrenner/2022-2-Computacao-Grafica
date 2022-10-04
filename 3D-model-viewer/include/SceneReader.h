#pragma once
#include <string>
#include <vector>
#include "SceneObject.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class SceneReader {
    public:
        SceneReader();
        float cameraInicialX;
        float cameraInicialY;
        float cameraInicialZ;
        std::vector<SceneObject*> sceneObjects = {};
        
        void read(string filename)
        {
            ifstream arq(filename);

            if (!arq) {
                exit(EXIT_FAILURE);
            }
            
            int aIndex = 0,
            bIndex = 0,
            cIndex = 0,
            linhaCount = 0,
            objCount = 0;
            
            SceneObject* sceneObject = new SceneObject();
            bool firstObj = true;

            while (!arq.eof()) {
                linhaCount++;
                string line;
                getline(arq, line);

                stringstream sline(line);

                string linha;
                sline >> linha;

                if (linha.empty()) {
                    continue;
                }

                if (linha == "#a") {
                    aIndex = linhaCount;
                } else if (linha == "#b") {
                    bIndex = linhaCount;
                } else if (linha == "#c") {
                    cIndex = linhaCount;
                }
                
            }
            arq.close();
            linhaCount = 0;
            
            ifstream arq1(filename);

            if (!arq1) {
                exit(EXIT_FAILURE);
            }
            
            while (!arq1.eof()) {
                linhaCount++;
                string line;
                getline(arq1, line);

                stringstream sline(line);

                string linha;
                sline >> linha;

                if (linha.empty()) {
                    continue;
                }

                if (linhaCount < aIndex) { continue; }
                else if (linhaCount == bIndex) { break; }
                
                if (linha == "#newobj") {
                    if (firstObj) {
                        firstObj = false;
                    } else {
                        objCount++;
                        sceneObject->objId = objCount;
                        sceneObjects.push_back(sceneObject);
                        sceneObject = new SceneObject();
                    }
                } else if (linha == "#i") {
                    string path;
                    sline >> path;
                    sceneObject->path = path;
                } else if (linha == "#ii") {
                    string rot, trans, escala;
                    float rotx, roty, rotz, transx, transy, transz, scalex, scaley, scalez;
                    sline >> transx >> transy >> transz >> rotx >> roty >> rotz >> scalex >> scaley >> scalez;
                    sceneObject->initalTrans = vec3(transx, transy, transz);
                    sceneObject->initalRot = vec3(rotx, roty, rotz);
                    sceneObject->initalEscale = vec3(scalex, scaley, scalez);
                } else if (linha == "#iii") {
                    
                }
            }
            
            objCount++;
            sceneObject->objId = objCount;
            sceneObjects.push_back(sceneObject);
            arq1.close();
            
            ifstream arq2(filename);

            if (!arq2) {
                exit(EXIT_FAILURE);
            }
            
            while (!arq2.eof()) {
                linhaCount++;
                string line;
                getline(arq2, line);

                stringstream sline(line);

                string linha;
                sline >> linha;

                if (linha.empty()) {
                    continue;
                }

                if (linhaCount < bIndex) { continue; }
                else if (linhaCount == cIndex) { break; }
                
                if (linha == "#b") {
                    
                }
            }
            arq2.close();
            
            ifstream arq3(filename);

            if (!arq3) {
                exit(EXIT_FAILURE);
            }
            
            while (!arq3.eof()) {
                linhaCount++;
                string line;
                getline(arq3, line);

                stringstream sline(line);

                string linha;
                sline >> linha;

                if (linha.empty()) {
                    continue;
                }

                if (linhaCount < cIndex) { continue; }
                
                if (linha == "#c") {
                    sline >> cameraInicialX >> cameraInicialY >> cameraInicialZ;
                }
            }

            arq3.close();
        }
};
