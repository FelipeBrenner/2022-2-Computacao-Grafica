#include "Mesh.h"
#include "Group.h"

Mesh::Mesh() {
	glm::vec3* vec = new glm::vec3(0.5f, -0.5f, 0.0f);
	this->vertex.push_back(vec);
	glm::vec3* vec1 = new glm::vec3(-0.5f, -0.5f, 0.0f);
	this->vertex.push_back(vec1);
	glm::vec3* vec2 = new glm::vec3(0.5f, 0.5f, 0.0f);
	this->vertex.push_back(vec2);
	glm::vec3* vec3 = new glm::vec3(-0.5f, 0.5f, 0.0f);
	this->vertex.push_back(vec3);

	glm::vec3* vec4 = new glm::vec3(0.5f, -0.5f, -1.0f);
	this->vertex.push_back(vec4);
	glm::vec3* vec5 = new glm::vec3(-0.5f, -0.5f, -1.0f);
	this->vertex.push_back(vec5);
	glm::vec3* vec6 = new glm::vec3(0.5f, 0.5f, -1.0f);
	this->vertex.push_back(vec6);
	glm::vec3* vec7 = new glm::vec3(-0.5f, 0.5f, -1.0f);
	this->vertex.push_back(vec7);

	glm::vec3* color = new glm::vec3(1.0f, 0.0f, 0.0f);
	this->mappings.push_back(color);
	glm::vec3* color1 = new glm::vec3(0.0f, 1.0f, 0.0f);
	this->mappings.push_back(color1);
	glm::vec3* color2 = new glm::vec3(0.0f, 0.0f, 1.0f);
	this->mappings.push_back(color2);

	Face* face = new Face;
	face->verts.push_back(0);
	face->verts.push_back(1);
	face->verts.push_back(2);
	face->textures.push_back(0);
	face->textures.push_back(1);
	face->textures.push_back(2);
	string t = "teste";
	/*
	Face* face2 = new Face;
	face2->verts.push_back(1);
	face2->verts.push_back(2);
	face2->verts.push_back(3);
	face2->textures.push_back(0);
	face2->textures.push_back(1);
	face2->textures.push_back(2);

	Face* face3 = new Face;
	face3->verts.push_back(0);
	face3->verts.push_back(2);
	face3->verts.push_back(6);
	face3->textures.push_back(0);
	face3->textures.push_back(1);
	face3->textures.push_back(2);

	Face* face4 = new Face;
	face4->verts.push_back(0);
	face4->verts.push_back(4);
	face4->verts.push_back(6);
	face4->textures.push_back(0);
	face4->textures.push_back(1);
	face4->textures.push_back(2);

	Face* face5 = new Face;
	face5->verts.push_back(3);
	face5->verts.push_back(7);
	face5->verts.push_back(6);
	face5->textures.push_back(0);
	face5->textures.push_back(1);
	face5->textures.push_back(2);

	Face* face6 = new Face;
	face6->verts.push_back(3);
	face6->verts.push_back(2);
	face6->verts.push_back(6);
	face6->textures.push_back(0);
	face6->textures.push_back(1);
	face6->textures.push_back(2);

	Face* face7 = new Face;
	face7->verts.push_back(5);
	face7->verts.push_back(7);
	face7->verts.push_back(6);
	face7->textures.push_back(0);
	face7->textures.push_back(1);
	face7->textures.push_back(2);

	Face* face8 = new Face;
	face8->verts.push_back(5);
	face8->verts.push_back(4);
	face8->verts.push_back(6);
	face8->textures.push_back(0);
	face8->textures.push_back(1);
	face8->textures.push_back(2);

	Face* face9 = new Face;
	face9->verts.push_back(1);
	face9->verts.push_back(5);
	face9->verts.push_back(4);
	face9->textures.push_back(0);
	face9->textures.push_back(1);
	face9->textures.push_back(2);

	Face* face10 = new Face;
	face10->verts.push_back(1);
	face10->verts.push_back(5);
	face10->verts.push_back(7);
	face10->textures.push_back(0);
	face10->textures.push_back(1);
	face10->textures.push_back(2);

	Face* face11 = new Face;
	face11->verts.push_back(1);
	face11->verts.push_back(3);
	face11->verts.push_back(7);
	face11->textures.push_back(0);
	face11->textures.push_back(1);
	face11->textures.push_back(2);

	Face* face12 = new Face;
	face12->verts.push_back(1);
	face12->verts.push_back(5);
	face12->verts.push_back(7);
	face12->textures.push_back(0);
	face12->textures.push_back(1);
	face12->textures.push_back(2);
	*/
	Group* group = new Group(t, t);

	group->faces.push_back(face);
	/*
	group->faces.push_back(face2);
	group->faces.push_back(face3);
	group->faces.push_back(face4);
	group->faces.push_back(face5);
	group->faces.push_back(face6);
	group->faces.push_back(face7);
	group->faces.push_back(face8);
	group->faces.push_back(face9);
	group->faces.push_back(face10);
	group->faces.push_back(face11);
	group->faces.push_back(face12);
	*/
	this->groups.push_back(group);
}

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
			glm::vec3* texture = new glm::vec3(x, y, 0);
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