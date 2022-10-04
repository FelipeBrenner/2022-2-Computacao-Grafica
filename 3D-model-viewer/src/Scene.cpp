#include "Scene.h"
#include "Mesh.h"
#include "Shader.h"

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

	shader = new Shader;
	
	vector <string> filenames;
	filenames.push_back("obj/pikachu.obj");
	
	mesh = new Mesh(filenames);

	for (Group* g : mesh->groups) {
		Material* material = mesh->materials[g->material];
		shader->loadTexture(strdup(material->texture.c_str()), strdup("texture1"), g->name);
		
		vector<float> vertices;
    vector<float> textures;

		for (Face* f : g->faces) {
			for (int verticeID : f->verts) {
				glm::vec3* vertice = mesh->vertex[verticeID - 1];
				vertices.push_back(vertice->x);
				vertices.push_back(vertice->y);
				vertices.push_back(vertice->z);

				g->numVertices++;
			}

			for (int textureID : f->textures) {
				glm::vec2* texture = mesh->mappings[textureID - 1];
				textures.push_back(texture->x);
				textures.push_back(texture->y);
			}
		}

		GLuint VBOvertices, VBOtextures, VAO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBOvertices);
		glGenBuffers(1, &VBOtextures);
		
		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
		glBindVertexArray(VAO);
		
		// Vertices
		glBindBuffer(GL_ARRAY_BUFFER, VBOvertices);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		
		// Textures
		glBindBuffer(GL_ARRAY_BUFFER, VBOtextures);
		glBufferData(GL_ARRAY_BUFFER, textures.size() * sizeof(float), textures.data(), GL_STATIC_DRAW);
		
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(2);
		
		g->vao = VAO;
		glBindVertexArray(0);
	}

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

		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		shader->setUniformMatrix4fv("view", view);
		float projection[] = {
			Sx, 0.0f, 0.0f, 0.0f,
			0.0f, Sy, 0.0f, 0.0f,
			0.0f, 0.0f, Sz, Pz,
			0.0f, 0.0f, -1.0f, 1.0f
		};
		shader->setUniformMatrix4fvFloat("projection", projection);

		/* wipe the drawing surface clear */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

void Scene::render() {
	for(Group* g : mesh->groups) {
		glBindVertexArray(g->vao);
		shader->useTexture(g->name);
		glDrawArrays(GL_TRIANGLES, 0, g->numVertices);
		glBindTexture( GL_TEXTURE_2D, 0);
	}
}

void Scene::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	const float cameraSpeed = 0.1f; // adjust accordingly
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