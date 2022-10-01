#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"

#include "Mesh.h"

using namespace std;

class Scene {
  public:
    Scene();

    void start();

  private:
    void initialize();
    void configureShaders();
    GLFWwindow* window;
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void processInput(GLFWwindow* window);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    Mesh* mesh;
    GLuint vao;
	  GLuint vbo;
    vector<float> vs1;
    vector<float> vts;
    vector<float> vns;
    const GLubyte* renderer;
	  const GLubyte* version;
    int viewLoc;
	  int projLoc;
};