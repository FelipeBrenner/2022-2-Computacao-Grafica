#include "System.h"
#include "SceneReader.h"

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

        mesh->objectName = sceneObj->name;
        mesh->translateModel(sceneObj->initalTrans);
        mesh->rotateModel(sceneObj->angle, sceneObj->initalRot);
        mesh->scaleModel(sceneObj->initalEscale);
        meshs.push_back(mesh);
    }

    system.Run(meshs);
    
    system.Finish();
    
    return 0;

}
