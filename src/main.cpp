#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "engine.h"

int main()
{
    // Создаем объект Window
    Engine* engine = new Engine(640, 480);
    engine->Init();

    // Цикл отрисовки
    while(engine->Run())
    {
        engine->Render();
    }

    return 0;
}

