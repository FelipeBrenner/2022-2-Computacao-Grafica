#pragma once
// Internal
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <math.h>

// External Libs
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM Includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Headers
#include "Shader.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "TranslatePointsReader.h"
#include "ObjReader.h"

class System {
    private:
        // Screen
        const GLint WIDTH = 1920, HEIGHT = 1080;
        int screenWidth, screenHeight;

    public:
        GLFWwindow* window;
        Shader coreShader;

    public:
        System();

        int GLFWInit();
        int OpenGLSetup();
        int SystemSetup();

        void Run(vector<Mesh*> meshs);
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
        static void processInput(GLFWwindow* window);
        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

        void Finish();
};