#pragma once
#include "Group.h"
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>     
#include <fstream> 
#include <sstream>
#include <bitset>

using namespace std;

class Mesh {
	public:
		Mesh(string filename);

		vector <Group*> groups;
		vector <glm::vec3*> vertex;
		vector <glm::vec3*> normals;
		vector <glm::vec2*> mappings;
};