#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class CurveReader {
public:
    CurveReader();
    
    vector<vec3*> read(string filename, float scale);
    float calculateAngle(vector<vec3*> curvePoints, int index);
};
