#include "System.h"
#include "SceneReader.h"

int main() {
    System system;
    
    if ( system.Init() != 0 ){
        return EXIT_FAILURE;
    }
    
    vector<Mesh*> meshs;
    
    SceneReader* sceneReader = new SceneReader();
    sceneReader->read("scene/scene.txt");

    for(SceneObject* sceneObj : sceneReader->sceneObjects) {
        string meshPath = sceneObj->path;
        Mesh* mesh = ObjReader::read(meshPath);

        mesh->objectName = sceneObj->name;
        mesh->translation = sceneObj->initalTrans;
        mesh->angle = sceneObj->angle;
        mesh->rotation = sceneObj->initalRot;
        mesh->scale = sceneObj->initalEscale;
        meshs.push_back(mesh);
    }

    system.Run(meshs);
    
    system.Finish();
    
    return 0;
}
