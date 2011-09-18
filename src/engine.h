#ifndef ENGINE_H
#define ENGINE_H

#include <SDL/SDL.h>
#include <ctime>
#include "screen.h"

class Engine
{
public:
    Engine(int width, int height);
    int Init(Screen* screen);
    bool Run();
    int Render();

    SDL_Surface* getScreen() { return surface; }

private:
    void Slock(SDL_Surface *surface);
    void Sulock(SDL_Surface *surface);
    void DrawPixel(SDL_Surface *surface, int x, int y, Uint8 R, Uint8 G, Uint8 B);
    void MakeScreenshot();

    SDL_Surface* surface;
    bool running;

    int width, height;
    Screen* screen;

    // FPS
    Uint32 startclock;
    Uint32 deltaclock;
    Uint32 raycount;

};

#endif // ENGINE_H
