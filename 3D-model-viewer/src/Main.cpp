#include "System.h"
#include "SceneReader.h"
#include <string>

int main() {
    System system;
    
    if ( system.Init() != 0 ){
        return EXIT_FAILURE;
    }
    
    vector<Mesh*> meshs;
    
    SceneReader* sceneReader = new SceneReader();
    sceneReader->read("Scene.txt");

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
