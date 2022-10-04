#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
using namespace glm;

class TranslatePointsReader {
    public:
        static vector<vec3*> read(string filename);
};


