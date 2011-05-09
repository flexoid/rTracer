#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "primitives/primitive.h"
#include "light.h"
#include "colorrgb.h"

class Scene
{
public:
    Scene();
    ~Scene();
    void AddPrimitive(Primitive*);
    void AddLight(Light*);

    std::vector< Primitive* > primitives;
    std::vector< Light* > lights;
    ColorRGB bgColor;
};

#endif // SCENE_H
