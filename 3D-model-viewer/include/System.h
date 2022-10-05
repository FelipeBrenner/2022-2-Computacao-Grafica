#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Mesh.h"
#include "ObjReader.h"

class System {

public:
    GLFWwindow* window;
    Shader coreShader;
    const GLint WIDTH = 1920, HEIGHT = 1080;
    int screenWidth, screenHeight;

    System();

    int Init();

    void Run(vector<Mesh*> meshs);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void processInput(GLFWwindow* window);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    void Finish();

};