#include "System.h"
#include "SceneReader.h"

int main() {
    System system;
    
    if ( system.GLFWInit() != 0 ){
        return EXIT_FAILURE;
    }
    if ( system.OpenGLSetup() != 0 ){
        return EXIT_FAILURE;
    }
    if ( system.SystemSetup() != 0 ){
        return EXIT_FAILURE;
    }
    
    vector<Mesh*> meshs;
    
    SceneReader* sceneReader = new SceneReader();
    sceneReader->read("objs/scene.txt");

    for(SceneObject* sceneObj : sceneReader->sceneObjects) {
        string meshPath = sceneObj->path;
        Mesh* mesh = ObjReader::read(meshPath);
        mesh->translateModel(sceneObj->initalTrans);
        mesh->rotateModel(sceneObj->initalRot);
        mesh->scaleModel(sceneObj->initalEscale);
        meshs.push_back(mesh);
    }
    

    system.Run(meshs);
    
    system.Finish();
    
    return 0;

}
