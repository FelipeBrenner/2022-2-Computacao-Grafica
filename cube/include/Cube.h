#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>

#include <iostream>     
#include <fstream> 
#include <sstream>
#include <bitset>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"

#include "Mesh.h"

using namespace std;

class Cube {
  public:
    Cube();

    void start();

  private:
    void initialize();
    GLFWwindow* window;
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void processInput(GLFWwindow* window);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    Mesh* read();
    Mesh* mesh;
};