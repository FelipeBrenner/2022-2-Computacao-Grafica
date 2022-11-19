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
    vector<vec3*> curvePoints;
    
    void read(string filename);
};
