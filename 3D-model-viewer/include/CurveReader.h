#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

#define PI 3.14159265359
#define HALF_PI PI/2.0

class CurveReader {
public:
    CurveReader();
    
    vector<vec3*> read(string filename, float scale);
    float calculateAngle(vector<vec3*> curvePoints, int index);
};
