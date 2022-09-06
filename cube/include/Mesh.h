#include "Includes.h"
#include "Group.h"

class Mesh {
	public:
		vector <Group*> groups;
		vector <vec3*> vertex;
		vector <vec3*> normals;
		vector <vec3*> mappings;
};