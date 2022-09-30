#include "Mesh.h"
#include "Group.h"

Mesh::Mesh(string filename) {
	Group* group = new Group;
	ifstream archive(filename);
	while (!archive.eof()) {
		string line;
		getline(archive, line);
		stringstream sline{};
		sline << line;
		string temp;
		sline >> temp;
		if (temp == "v") {
			float x, y, z;
			sline >> x >> y >> z;
			glm::vec3* vertex = new glm::vec3(x, y, z);
			this->vertex.push_back(vertex);
		}
		else if (temp == "vt") {
			float x, y;
			sline >> x >> y;
			glm::vec2* texture = new glm::vec2(x, y);
			this->mappings.push_back(texture);
		}
		else if (temp == "f") {
			// implementar lógica de varições
			// para face: v, v/t/n, v/t e v//n
			// while enquanto tem tokens em sline:
			//cout << sline << endl;
			string x;

			Face* face = new Face;
			while (sline >> x) {
				stringstream stoken;
				stoken << x;
				string aux;

				int faceValues[3] = { -1, -1, -1 };
				int i = 0;

				while (getline(stoken, aux, '/')) {
					if (aux != "") {
						faceValues[i] = stoi(aux);
					}
					i++;
				}
				face->verts.push_back(faceValues[0]);

				if (faceValues[1] != -1) {
					face->textures.push_back(faceValues[1]);
				}

				if (faceValues[2] != -1) {
					face->norms.push_back(faceValues[2]);
				}

				Face* face = new Face;
			}
			group->faces.push_back(face);
		}
	}
	this->groups.push_back(group);
}