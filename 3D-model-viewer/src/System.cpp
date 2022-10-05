#include "System.h"
#include "Mesh.h"

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraPos = glm::vec3(1.0f, 0.0f, 1.0f);
bool firstMouse = true;
float yawVariable = -90.0f;
float pitchVariable = 0.0f;
float lastX = 1920 / 2.0;
float lastY = 1080 / 2.0;

float fov = 45.0f;

enum RotationStatus {
    none, X, Y, Z
};

System::System() {}

int System::Init() {
    
    glfwInit();
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    glfwWindowHint( GLFW_SAMPLES, 4 );
    
    window = glfwCreateWindow( WIDTH, HEIGHT, "3D Model Viewer", nullptr, nullptr );
    
    glfwGetFramebufferSize( window, &screenWidth, &screenHeight );
    
    if ( window == nullptr ) {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    
    glewExperimental = GL_TRUE;
    
    if ( glewInit() != GLEW_OK ) {
        std::cout << "Failed no init GLEW." << std::endl;
        return EXIT_FAILURE;
    }
    
    glViewport( 0, 0, screenWidth, screenHeight );
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    
    coreShader = Shader("shaders/core.vert", "shaders/core.frag");
    coreShader.Use();

    return EXIT_SUCCESS;
}

void System::Run(vector<Mesh*> meshs) {
    glfwSetFramebufferSizeCallback(window, System::framebuffer_size_callback);
    glfwSetCursorPosCallback (window, System::mouse_callback);
    glfwSetScrollCallback(window, System::scroll_callback);
    
    for (Mesh* mesh : meshs) {
        for (Group* group : mesh->getGroups()) {
            
            Material* material = mesh->getMaterial(group->getMaterial());
            coreShader.LoadTexture(strdup(material->getTexture().c_str()), strdup("texture1"), group->getName());
            vector<float> vertices;
            vector<float> textures;
            
            for (Face* face : group->getFaces()) {
                for (int verticeID : face->getVertices()) {
                    glm::vec3* vertice = mesh->vertice(verticeID - 1);
                    vertices.push_back(vertice->x);
                    vertices.push_back(vertice->y);
                    vertices.push_back(vertice->z);
                    
                    group->increaseNumVertices();
                }
                
                for (int textureID : face->getTextures()) {
                    glm::vec2* texture = mesh->texture(textureID - 1);
                    textures.push_back(texture->x);
                    textures.push_back(texture->y);
                }
            }
            
            GLuint VBOvertices, VBOtextures, VAO;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBOvertices);
            glGenBuffers(1, &VBOtextures);
            glBindVertexArray(VAO);
            
            // Vertices
            glBindBuffer(GL_ARRAY_BUFFER, VBOvertices);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
            
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
            glEnableVertexAttribArray(0);
            
            // Textures
            glBindBuffer(GL_ARRAY_BUFFER, VBOtextures);
            glBufferData(GL_ARRAY_BUFFER, textures.size() * sizeof(float), textures.data(), GL_STATIC_DRAW);
            
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
            glEnableVertexAttribArray(1);
            
            group->setVAO(&VAO);
            glBindVertexArray(0);
        }
    }
    
    float angle = 0.0f;
    float translateX = 0.0f;
    float translateY = 0.0f;
    float translateZ = 0.0f;
    float camX = 1.0f;
    float camY = 0.5f;
    float camZ = 1.0f;

    glm::mat4 view;

    RotationStatus rotationStatus = none;
    while ( !glfwWindowShouldClose( window ) ) {
        
        glfwPollEvents();

        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        coreShader.Use();

        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        coreShader.setMatrix4fv("view", view);

        glm::mat4 proj = glm::perspective(glm::radians(fov), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
        coreShader.setMatrix4fv("projection", proj);

        for (Mesh* mesh : meshs) {
            mesh->model = glm::translate(mesh->model, glm::vec3(translateX, translateY, translateZ));
        }
        
        for (Mesh* mesh : meshs) {
            coreShader.setMatrix4fv("model", mesh->model);
            
            for (Group* group : mesh->getGroups()) {
                coreShader.UseTexture(group->getName());
                glBindVertexArray(group->getVAO());
                glDrawArrays(GL_TRIANGLES, 0, group->getNumVertices());
                glBindVertexArray(0);
                glBindTexture(GL_TEXTURE_2D, 0);
            }
        }
        
        glfwSwapBuffers(window);
        processInput(window);
    }
}

void System::Finish() {
    coreShader.Delete();
    
    glfwTerminate();
}

void System::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    const float cameraSpeed = 0.05f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void System::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void System::mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
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

void System::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    fov -= (float)yoffset * 10;
}