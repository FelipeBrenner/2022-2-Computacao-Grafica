#include "System.h"
#include "Mesh.h"
#include "CurveReader.h"

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraPos = glm::vec3(0.0f, 4.0f, 20.0f);
bool firstMouse = true;
float yawVariable = -90.0f;
float pitchVariable = 0.0f;
float lastX = 1920 / 2.0;
float lastY = 1080 / 2.0;

bool bulletWasFired = false;

float curveScale = 20.0f;
int carPosition = 1;
vector<vec3*> curvePoints;

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
        cout << "Failed to create GLFW Window" << endl;
        glfwTerminate();
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    
    glewExperimental = GL_TRUE;
    
    if ( glewInit() != GLEW_OK ) {
        cout << "Failed no init GLEW." << endl;
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

    CurveReader* curveReader = new CurveReader();
    curvePoints = curveReader->read("scene/pista.txt", curveScale);
    
    for (Mesh* mesh : meshs) {
        for (Group* group : mesh->getGroups()) {
            Material* material = mesh->getMaterial(group->getMaterial());
            coreShader.LoadTexture(strdup(material->getTexture().c_str()), strdup("texture1"), group->getName());
            vector<float> vertices;
            vector<float> textures;
            vector<float> normais;
            vector<float> ambientLight;
            vector<float> diffuseLight;
            vector<float> specularLight;
            vector<float> shininessLight;

            
            for (Face* face : group->getFaces()) {
                for (int verticeID : face->getVertices()) {
                    glm::vec3* vertice = mesh->vertice(verticeID - 1);
                    if(vertice != NULL) {
                        vertices.push_back(vertice->x);
                        vertices.push_back(vertice->y);
                        vertices.push_back(vertice->z);

                        ambientLight.push_back(material->getAmbient()->x);
                        ambientLight.push_back(material->getAmbient()->y);
                        ambientLight.push_back(material->getAmbient()->z);

                        diffuseLight.push_back(material->getDiffuse()->x);
                        diffuseLight.push_back(material->getDiffuse()->y);
                        diffuseLight.push_back(material->getDiffuse()->z);

                        /*
                        specularLight.push_back(material->getSpecular()->x);
                        specularLight.push_back(material->getSpecular()->y);
                        specularLight.push_back(material->getSpecular()->z);
                        */
                        specularLight.push_back(0.0f);
                        specularLight.push_back(0.0f);
                        specularLight.push_back(0.0f);

                        shininessLight.push_back(material->getShininess());

                    }
                    
                    group->increaseNumVertices();
                }
                
                for (int textureID : face->getTextures()) {
                    glm::vec2* texture = mesh->texture(textureID - 1);
                    if (texture != NULL) {
                        textures.push_back(texture->x);
                        textures.push_back(texture->y);
                    }
                }
                
                for (int normalID : face->getNormais()) {
                    glm::vec3* normal = mesh->normal(normalID - 1);
                    if (normal != NULL) {
                        normais.push_back(normal->x);
                        normais.push_back(normal->y);
                        normais.push_back(normal->z);
                    }
                }
            }
            
            GLuint VBOvertices, VBOtextures, VBOnormais, VBOamb, VBOdiff, VBOspec, VBOshin, VAO;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBOvertices);
            glGenBuffers(1, &VBOtextures);
            glGenBuffers(1, &VBOnormais);
            glGenBuffers(1, &VBOamb);
            glGenBuffers(1, &VBOdiff);
            glGenBuffers(1, &VBOspec);
            glGenBuffers(1, &VBOshin);

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

            // Normais
            glBindBuffer(GL_ARRAY_BUFFER, VBOnormais);
            glBufferData(GL_ARRAY_BUFFER, normais.size() * sizeof(float), normais.data(), GL_STATIC_DRAW);

            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
            glEnableVertexAttribArray(2);

            // Ambient
            glBindBuffer(GL_ARRAY_BUFFER, VBOamb);
            glBufferData(GL_ARRAY_BUFFER, ambientLight.size() * sizeof(float), ambientLight.data(), GL_STATIC_DRAW);

            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
            glEnableVertexAttribArray(3);

            // Diffuse
            glBindBuffer(GL_ARRAY_BUFFER, VBOdiff);
            glBufferData(GL_ARRAY_BUFFER, diffuseLight.size() * sizeof(float), diffuseLight.data(), GL_STATIC_DRAW);

            glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
            glEnableVertexAttribArray(4);

            // Specular
            glBindBuffer(GL_ARRAY_BUFFER, VBOspec);
            glBufferData(GL_ARRAY_BUFFER, specularLight.size() * sizeof(float), specularLight.data(), GL_STATIC_DRAW);

            glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
            glEnableVertexAttribArray(5);

            // Shininess
            glBindBuffer(GL_ARRAY_BUFFER, VBOshin);
            glBufferData(GL_ARRAY_BUFFER, shininessLight.size() * sizeof(float), shininessLight.data(), GL_STATIC_DRAW);

            glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat), (GLvoid*)0);
            glEnableVertexAttribArray(6);
            
            group->setVAO(&VAO);
            glBindVertexArray(0);
        }
    }

    float angle = 0.0f;
    float camX = 1.0f;
    float camY = 0.5f;
    float camZ = 1.0f;

    glm::mat4 view;

    RotationStatus rotationStatus = none;

    clock_t time = clock();

    while ( !glfwWindowShouldClose( window ) ) {
        
        glfwPollEvents();

        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        coreShader.Use();

        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        coreShader.setMatrix4fv("view", view);

        glm::mat4 proj = glm::perspective(glm::radians(fov), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
        coreShader.setMatrix4fv("projection", proj);

        coreShader.setVec3("lightColor", vec3(1.0f, 1.0f, 1.0f));
        coreShader.setVec3("lightPos", vec3(100.0f, 1.0f, 100.0f));
        coreShader.setVec3("viewPos", vec3(camX, camY, camZ));
        coreShader.setVec3("cameraPos", cameraPos);

        Mesh* meshsAfterCollision;
        
        for (Mesh* mesh : meshs) {
            // if (mesh->objectName == "bullet" && bulletWasFired) {
            //     mesh->translateModel(vec3(0.0f, 0.0f, -0.01f));
            // }

            if (mesh->eliminable) {
                for (Mesh* otherMesh : meshs) {
                    bool hasOtherEliminable = otherMesh->eliminable && mesh != otherMesh;
                    if (hasOtherEliminable) {
                        bool hasCollidedX = mesh->translation.x + mesh->xHitbox > otherMesh->translation.x - otherMesh->xHitbox && mesh->translation.x - mesh->xHitbox < otherMesh->translation.x + otherMesh->xHitbox;
                        bool hasCollidedY = mesh->translation.y + mesh->yHitbox > otherMesh->translation.y - otherMesh->yHitbox && mesh->translation.y - mesh->yHitbox < otherMesh->translation.y + otherMesh->yHitbox;
                        bool hasCollidedZ = mesh->translation.z + mesh->zHitbox > otherMesh->translation.z - otherMesh->zHitbox && mesh->translation.z - mesh->zHitbox < otherMesh->translation.z + otherMesh->zHitbox;

                        if (hasCollidedX && hasCollidedY && hasCollidedZ) {
                            mesh->eliminated = true;
                        }
                    }
                }
            }

            if(mesh->objectName == "curve") {
                mesh->scale = vec3(curveScale);
            }

            if (mesh->objectName == "car" && (clock() - time) / 1000000.0 > 0.03) {
                // mesh->xAngle = curveReader->calculateAngle(curvePoints, carPosition, 'x');
                mesh->yAngle = curveReader->calculateAngle(curvePoints, carPosition, 'y');
                // mesh->zAngle = curveReader->calculateAngle(curvePoints, carPosition, 'z');

                mesh->translation = vec3(curvePoints.at(carPosition)->x, curvePoints.at(carPosition)->y, curvePoints.at(carPosition)->z);
                
                carPosition++;
                if(carPosition == curvePoints.size()-2) carPosition = 0;
                time = clock();
            }

            mat4 model = mat4(1);
            model = translate(model, mesh->translation);
            // model = rotate(model, mesh->xAngle, vec3(1,0,0));
            model = rotate(model, mesh->yAngle, vec3(0,1,0));
            // model = rotate(model, mesh->zAngle, vec3(0,0,1));
            model = scale(model, mesh->scale);

            coreShader.setMatrix4fv("model", model);

            for (Group* group : mesh->getGroups()) {
                coreShader.UseTexture(group->getName());
                glBindVertexArray(group->getVAO());
                glDrawArrays(GL_TRIANGLES, 0, group->getNumVertices());
                glBindVertexArray(0);
                glBindTexture(GL_TEXTURE_2D, 0);
            }   
        }

        for (int i=0; i<meshs.size(); i++) {
            if (meshs.at(i)->eliminated) meshs.erase(meshs.begin() + i);
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

    const float cameraSpeed = 0.01f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        bulletWasFired = true;
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

    float sensitivity = 0.05f; // change this value to your liking
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
