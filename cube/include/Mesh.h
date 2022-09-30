#pragma once
#include "Group.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class Mesh {
	public:
		Mesh();

		vector <Group*> groups;
		vector <glm::vec3*> vertex;
		vector <glm::vec3*> normals;
		vector <glm::vec3*> mappings;
};