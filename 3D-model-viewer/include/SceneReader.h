#pragma once
#include <string>
#include <vector>
#include "SceneObject.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class SceneReader
{
public:
    SceneReader();
    float cameraInicialX;
    float cameraInicialY;
    float cameraInicialZ;
    vector<SceneObject*> sceneObjects;
    
    void read(string filename);

};
