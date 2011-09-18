#ifndef SCENEPARSER_H
#define SCENEPARSER_H

#include <vector>
#include <map>
#include <string.h>
#include "scene.h"
#include "material.h"
#include "light.h"
#include "camera.h"
#include "primitives/sphere.h"
#include "primitives/plane.h"
#include "primitives/prism.h"

class SceneParser
{
public:
    Scene* LoadScene(const char* filename);

private:
    Prism* ParsePrism(const char* str);
    Plane* ParsePlane(const char* str);
    Sphere* ParseSphere(const char* str);

    Light* ParseLight(const char* str);
    Camera* ParseCamera(const char* str);
    Material* ParseMaterial(const char* str);
    ColorRGB ParseColor(const char* str);

    char* fgets_nocomm(char* s, int size, FILE* stream);

    std::map< int, Material* > materials;
};

#endif // SCENEPARSER_H
