#pragma once
#include <vector>

using namespace std;
class Face {
  public:
    Face();

    vector <int> verts;
    vector <int> norms;
    vector <int> textures;
};