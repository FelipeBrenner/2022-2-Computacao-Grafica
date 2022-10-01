#include "Scene.h"
#include "Mesh.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraPos = glm::vec3(1.0f, 0.0f, 1.0f);
bool firstMouse = true;
float yawVariable = -90.0f;	// yawVariable is initialized to -90.0 degrees since a yawVariable of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitchVariable = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

Scene::Scene() {}

void Scene::start() {
	initialize();

	texture1;
	// texture 1
	// ---------
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	//glActiveTexture(GL_TEXTURE0);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load and generate the texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load("images/loud.jpeg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	vector <string> filenames;
	filenames.push_back("obj/pyramid.obj");
	filenames.push_back("obj/pikachu.obj");
	mesh = new Mesh(filenames);

	for (Group* g : mesh->groups) {
		for (Face* f : g->faces) {
			for (int i = 0; i < f->verts.size(); i++) {
				glm::vec3* v = mesh->vertex[f->verts[i] - 1];
				vs1.push_back(v->x);
				vs1.push_back(v->y);
				vs1.push_back(v->z);
				if (f->textures.size()) {
					glm::vec2* vt = mesh->mappings[f->textures[i] - 1];
					vts.push_back(vt->x);
					vts.push_back(vt->y);
				}

				if (i > 2) {
					glm::vec3* v1 = mesh->vertex[f->verts[2] - 1];
					vs1.push_back(v1->x);
					vs1.push_back(v1->y);
					vs1.push_back(v1->z);
					if (f->textures.size()) {
						glm::vec2* vt1 = mesh->mappings[f->textures[2] - 1];
						vts.push_back(vt1->x);
						vts.push_back(vt1->y);
					}
					glm::vec3* v2 = mesh->vertex[f->verts[0] - 1];
					vs1.push_back(v2->x);
					vs1.push_back(v2->y);
					vs1.push_back(v2->z);
					if (f->textures.size()) {
						glm::vec2* vt2 = mesh->mappings[f->textures[0] - 1];
						vts.push_back(vt2->x);
						vts.push_back(vt2->y);
					}
				}
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
	
		GLuint vbo;

		/* a vertex buffer object (VBO) is created here. this stores an array of data
		on the graphics adapter's memory. in our case - the vertex points */
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vs1.size(), vs1.data(), GL_STATIC_DRAW);

		glGenVertexArrays(1, &g->vao);
		glBindVertexArray(g->vao);
		glEnableVertexAttribArray(0); // habilitado primeiro atributo do vbo bound atual
		glBindBuffer(GL_ARRAY_BUFFER, vbo); // identifica vbo atual
		// associa��o do vbo atual com primeiro atributo
		// 0 identifica que o primeiro atributo est� sendo definido
		// 3, GL_FLOAT identifica que dados s�o vec3 e est�o a cada 3 float.
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		GLuint texturesVBO;
		glGenBuffers(1, &texturesVBO);
		glBindBuffer(GL_ARRAY_BUFFER, texturesVBO);
		glBufferData(GL_ARRAY_BUFFER, vts.size() * sizeof(GLfloat), vts.data(), GL_STATIC_DRAW);

		// texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
	}

	configureShaders();

	glClearColor(0.6f, 0.6f, 0.8f, 1.0f);

	/* this loop clears the drawing surface, then draws the geometry described by
	the VAO onto the drawing surface. we 'poll events' to see if the window was
	closed, etc. finally, we 'swap the buffers' which displays our drawing surface
	onto the view area. we use a double-buffering system which means that we have
	a 'currently displayed' surface, and 'currently being drawn' surface. hence
	the 'swap' idea. in a single-buffering system we would see stuff being drawn
	one-after-the-other */

	glm::mat4 view;
	float near = 0.1;
	float far = 100.0;
	float aspect = 640.0 / 480.0;

	while (!glfwWindowShouldClose(window)) {
		float range = tan(fov * 0.5) * near;
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

		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, projection);

		/* wipe the drawing surface clear */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//		glUseProgram (shader_programme);

		render();

		/* update other events like input handling */
		glfwPollEvents();
		/* put the stuff we've been drawing onto the display */
		glfwSwapBuffers(window);

		processInput(window);
	}

	/* close GL context and any other GLFW resources */
	glfwTerminate();
}

void Scene::initialize() {
	// glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);

	//Define callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		/* start GL context and O/S window using the GLFW helper library */
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
	}

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
}

void Scene::configureShaders() {
		/* these are the strings of code for the shaders
	the vertex shader positions each vertex point */
	/* these are the strings of code for the shaders
	the vertex shader positions each vertex point */
	const char* vertex_shader =
		"#version 410\n"
		"layout(location=0) in vec3 vp;"
		"layout(location=1) in vec2 aTexCoord;"
		"uniform mat4 view;"
		"uniform mat4 projection;"
		"out vec2 TexCoord;"
		"void main () {"
		"   TexCoord = aTexCoord;"
		"	gl_Position = projection * view * vec4 (vp, 1.0);"
		"}";

	/* the fragment shader colours each fragment (pixel-sized area of the
	triangle) */
	const char* fragment_shader =
		"#version 410\n"
		"in vec2 TexCoord;"
		"uniform sampler2D texture1;"
		"out vec4 frag_color;"
		"void main () {"
		//"	frag_color = vec4 (color, 1.0);"
		"	frag_color = texture(texture1, TexCoord);"
		"}";

	/* GL shader objects for vertex and fragment shader [components] */
	GLuint vs, fs;
	/* GL shader programme object [combined, to link] */
	GLuint shader_programme;

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

	viewLoc = glGetUniformLocation(shader_programme, "view");
	projLoc = glGetUniformLocation(shader_programme, "projection");
	glUseProgram(shader_programme);
}

void Scene::render() {
	for(Group* g : mesh->groups) {
		//glUseProgram(shader_programme);
		glBindTexture(GL_TEXTURE_2D, texture1);
		//glActiveTexture(GL_TEXTURE0);

		//glUseProgram(shader_programme);
		glBindVertexArray(g->vao);
		/* draw points 0-3 from the currently bound VAO with current in-use shader*/
		glDrawArrays(GL_TRIANGLES, 0, vs1.size() / 3);
		glBindVertexArray(0);
	}
}

void Scene::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	const float cameraSpeed = 0.0005f; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Scene::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Scene::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yawVariable += xoffset;
	pitchVariable += yoffset;

	// make sure that when pitchVariable is out of bounds, screen doesn't get flipped
	if (pitchVariable > 89.0f)
		pitchVariable = 89.0f;
	if (pitchVariable < -89.0f)
		pitchVariable = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yawVariable)) * cos(glm::radians(pitchVariable));
	front.y = sin(glm::radians(pitchVariable));
	front.z = sin(glm::radians(yawVariable)) * cos(glm::radians(pitchVariable));
	cameraFront = glm::normalize(front);
}

void Scene::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	fov -= (float)yoffset * 0.1;
}