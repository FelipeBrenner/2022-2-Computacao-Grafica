#include "Includes.h"
#include "Mesh.h"

/*
	Unisinos
	Computação Gráfica - 2022/2
	Felipe Brenner
	Leonardo Veiga
	Lucas Oliveira
*/


int main() {
	GLFWwindow* window = NULL;
	const GLubyte* renderer;
	const GLubyte* version;
	GLuint vao, vao2;
	GLuint vbo, vbo2;
	/* geometry to use. these are 3 xyz points (9 floats total) to make a triangle
	*/

	float matrix[] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	Mesh* mesh = new Mesh;
	glm::vec3* vec = new glm::vec3(0.5f, -0.5f, 0.0f);
	mesh->vertex.push_back(vec);
	glm::vec3* vec1 = new glm::vec3(-0.5f, -0.5f, 0.0f);
	mesh->vertex.push_back(vec1);
	glm::vec3* vec2 = new glm::vec3(0.5f, 0.5f, 0.0f);
	mesh->vertex.push_back(vec2);
	glm::vec3* vec3 = new glm::vec3(-0.5f, 0.5f, 0.0f);
	mesh->vertex.push_back(vec3);
	
	glm::vec3* vec4 = new glm::vec3(0.5f, -0.5f, -1.0f);
	mesh->vertex.push_back(vec4);
	glm::vec3* vec5 = new glm::vec3(-0.5f, -0.5f, -1.0f);
	mesh->vertex.push_back(vec5);
	glm::vec3* vec6 = new glm::vec3(0.5f, 0.5f, -1.0f);
	mesh->vertex.push_back(vec6);
	glm::vec3* vec7 = new glm::vec3(-0.5f, 0.5f, -1.0f);
	mesh->vertex.push_back(vec7);

	glm::vec3* color = new glm::vec3(1.0f, 0.0f, 0.0f);
	mesh->mappings.push_back(color);
	glm::vec3* color1 = new glm::vec3(0.0f, 1.0f, 0.0f);
	mesh->mappings.push_back(color1);
	glm::vec3* color2 = new glm::vec3(0.0f, 0.0f, 1.0f);
	mesh->mappings.push_back(color2);

	Face* face = new Face;
	face->verts.push_back(0);
	face->verts.push_back(1);
	face->verts.push_back(2);
	face->texts.push_back(0);
	face->texts.push_back(1);
	face->texts.push_back(2);
	string t = "teste";

	Face* face2 = new Face;
	face2->verts.push_back(1);
	face2->verts.push_back(2);
	face2->verts.push_back(3);
	face2->texts.push_back(0);
	face2->texts.push_back(1);
	face2->texts.push_back(2);

	/*
		12
		34
		56
		78
		910
		1112
	*/

	Face* face3 = new Face;
	face3->verts.push_back(0);
	face3->verts.push_back(2);
	face3->verts.push_back(6);
	face3->texts.push_back(0);
	face3->texts.push_back(1);
	face3->texts.push_back(2);

	Face* face4 = new Face;
	face4->verts.push_back(0);
	face4->verts.push_back(4);
	face4->verts.push_back(6);
	face4->texts.push_back(0);
	face4->texts.push_back(1);
	face4->texts.push_back(2);

	Face* face5 = new Face;
	face5->verts.push_back(3);
	face5->verts.push_back(7);
	face5->verts.push_back(6);
	face5->texts.push_back(0);
	face5->texts.push_back(1);
	face5->texts.push_back(2);

	Face* face6 = new Face;
	face6->verts.push_back(3);
	face6->verts.push_back(2);
	face6->verts.push_back(6);
	face6->texts.push_back(0);
	face6->texts.push_back(1);
	face6->texts.push_back(2);

	Face* face7 = new Face;
	face7->verts.push_back(5);
	face7->verts.push_back(7);
	face7->verts.push_back(6);
	face7->texts.push_back(0);
	face7->texts.push_back(1);
	face7->texts.push_back(2);

	Face* face8 = new Face;
	face8->verts.push_back(5);
	face8->verts.push_back(4);
	face8->verts.push_back(6);
	face8->texts.push_back(0);
	face8->texts.push_back(1);
	face8->texts.push_back(2);

	Face* face9 = new Face;
	face9->verts.push_back(1);
	face9->verts.push_back(5);
	face9->verts.push_back(4);
	face9->texts.push_back(0);
	face9->texts.push_back(1);
	face9->texts.push_back(2);

	Face* face10 = new Face;
	face10->verts.push_back(1);
	face10->verts.push_back(5);
	face10->verts.push_back(7);
	face10->texts.push_back(0);
	face10->texts.push_back(1);
	face10->texts.push_back(2);

	Face* face11 = new Face;
	face11->verts.push_back(1);
	face11->verts.push_back(3);
	face11->verts.push_back(7);
	face11->texts.push_back(0);
	face11->texts.push_back(1);
	face11->texts.push_back(2);

	Face* face12 = new Face;
	face12->verts.push_back(1);
	face12->verts.push_back(5);
	face12->verts.push_back(7);
	face12->texts.push_back(0);
	face12->texts.push_back(1);
	face12->texts.push_back(2);

	Group* group = new Group(t, t);

	group->faces.push_back(face);
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

	mesh->groups.push_back(group);

	vector<float> vs1;
	vector<float> vts;
	vector<float> vns;
	for (Group* g : mesh->groups) {
		for (Face* f : g->faces) {
			for (int i = 0; i < f->verts.size(); i++) {
				glm::vec3* v = mesh->vertex[f->verts[i]];
				vs1.push_back(v->x);
				vs1.push_back(v->y);
				vs1.push_back(v->z);
				glm::vec3* vt = mesh->mappings[f->texts[i]];
				vts.push_back(vt->x);
				vts.push_back(vt->y);
				vts.push_back(vt->z);
				//auto vn = mesh->normals[f->norms[i]];
				//vns.push_back(vn->x);
				//vns.push_back(vn->y);
				//vns.push_back(vn->z);
			}
		}
		// 1) criar VAO para o grupo
		// 2) associar VAO criado com grupo
		// 3) criar um VBO para vs
		// 4) criar um VBO para vts
		// 5) criar um VBO para vns
		// 6) definir layout e atributos do VAO 
		// para leitura dos VBOs
	}

	/* these are the strings of code for the shaders
	the vertex shader positions each vertex point */
	const char* vertex_shader =
		"#version 410\n"
		"layout(location=0) in vec3 vp;"
		"layout(location=1) in vec3 vc;"
		"uniform mat4 view;"
		"uniform mat4 projection;"
		"out vec3 color;"
		"void main () {"
		"   color = vc;"
		"	gl_Position = projection * view * vec4 (vp, 1.0);"
		"}";

	/* the fragment shader colours each fragment (pixel-sized area of the
	triangle) */
	const char* fragment_shader =
		"#version 410\n"
		"in vec3 color;"
		"out vec4 frag_color;"
		"void main () {"
		"	frag_color = vec4 (color, 1.0);"
		"}";
	/* GL shader objects for vertex and fragment shader [components] */
	GLuint vs, fs, fs2;
	/* GL shader programme object [combined, to link] */
	GLuint shader_programme, shader_programme2;

	/* start GL context and O/S window using the GLFW helper library */
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

	/* change to 3.2 if on Apple OS X */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(
		640, 480, "CGR - GLSL - 03 - Moving Triangle", NULL, NULL
	);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	/* start GLEW extension handler */
	glewExperimental = GL_TRUE;
	glewInit();

	/* get version info */
	renderer = glGetString(GL_RENDERER); /* get renderer string */
	version = glGetString(GL_VERSION); /* version as a string */
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	/* tell GL to only draw onto a pixel if the shape is closer to the viewer */
	glEnable(GL_DEPTH_TEST); /* enable depth-testing */
	glDepthFunc(GL_LESS);/*depth-testing interprets a smaller value as "closer"*/

	/* a vertex buffer object (VBO) is created here. this stores an array of data
	on the graphics adapter's memory. in our case - the vertex points */
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vs1.size(), vs1.data(), GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0); // habilitado primeiro atributo do vbo bound atual
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // identifica vbo atual
	// associa��o do vbo atual com primeiro atributo
	// 0 identifica que o primeiro atributo est� sendo definido
	// 3, GL_FLOAT identifica que dados s�o vec3 e est�o a cada 3 float.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// � poss�vel associar outros atributos, como normais, mapeamento e cores
	// lembre-se: um por v�rtice!
	GLuint colorsVBO;
	glGenBuffers(1, &colorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, vts.size() * sizeof(GLfloat), vts.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	// note que agora o atributo 1 est� definido
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1); // habilitado segundo atributo do vbo bound atual

	/* here we copy the shader strings into GL shaders, and compile them. we then
	create an executable shader 'program' and attach both of the compiled shaders.
	we link this, which matches the outputs of the vertex shader to the inputs of
	the fragment shader, etc. and it is then ready to use */
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	int viewLoc = glGetUniformLocation(shader_programme, "view");
	int projLoc = glGetUniformLocation(shader_programme, "projection");
	//glUseProgram (shader_programme);
	//glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, matrix);

	glClearColor(0.6f, 0.6f, 0.8f, 1.0f);

	/* this loop clears the drawing surface, then draws the geometry described by
	the VAO onto the drawing surface. we 'poll events' to see if the window was
	closed, etc. finally, we 'swap the buffers' which displays our drawing surface
	onto the view area. we use a double-buffering system which means that we have
	a 'currently displayed' surface, and 'currently being drawn' surface. hence
	the 'swap' idea. in a single-buffering system we would see stuff being drawn
	one-after-the-other */

	float speed = 1.0f;
	float lastPosition = 0.0f;
	glm::vec3 cameraPos = glm::vec3(1.0f, 0.0f, 1.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view;
	glUseProgram(shader_programme);



	float near = 0.1;
	float far = 100.0;
	float range = tan(90 * 0.5) * near;
	float aspect = 640.0 / 480.0;

	float Sx = (2 * near) / (range / aspect + range / aspect);
	float Sy = near / range;
	float Sz = -(far + near) / (far - near);
	float Pz = -(2 * far * near) / (far - near);


	float projection[] = {
	Sx, 0.0f, 0.0f, 0.0f,
	0.0f, Sy, 0.0f, 0.0f,
	0.0f, 0.0f, Sz, Pz,
	0.0f, 0.0f, -1.0f, 1.0f
	};


	while (!glfwWindowShouldClose(window)) {
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		const float cameraSpeed = 0.05f; // adjust accordingly
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		
		
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, projection);


		//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		/* wipe the drawing surface clear */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//		glUseProgram (shader_programme);

		glBindVertexArray(vao);
		/* draw points 0-3 from the currently bound VAO with current in-use shader*/
		glDrawArrays(GL_TRIANGLES, 0, vs1.size() / 3);

		/* update other events like input handling */
		glfwPollEvents();
		/* put the stuff we've been drawing onto the display */
		glfwSwapBuffers(window);
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, 1);
		}
	}

	/* close GL context and any other GLFW resources */
	glfwTerminate();
	return 0;
}