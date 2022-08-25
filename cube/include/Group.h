#include "Includes.h"
#include "Face.h"

class Group {
  public:
    string name;
    string material;
    vector<Face*> faces;
    GLuint vao;

    Group(string n, string m);
};
