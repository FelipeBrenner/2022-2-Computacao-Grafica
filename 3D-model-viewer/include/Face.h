#pragma once
#include <vector>
#include <string>

using namespace std;
class Face {
  public:
    Face();

    vector <int> verts;
    vector <int> norms;
    vector <int> textures;
    string mtl;
};