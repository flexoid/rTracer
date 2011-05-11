#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "primitives/primitive.h"
#include "light.h"
#include "colorrgb.h"
#include "camera.h"

class Scene
{
public:
    Scene();
    Scene(ColorRGB);
    ~Scene();
    void AddPrimitive(Primitive*);
    void AddLight(Light*);
    void AddCamera(Camera*);

    std::vector< Primitive* > primitives;
    std::vector< Light* > lights;
    Camera* camera;
    ColorRGB bgColor;
};

#endif // SCENE_H
