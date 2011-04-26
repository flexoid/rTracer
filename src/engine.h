#ifndef WINDOW_H
#define WINDOW_H

#include <SDL/SDL.h>

class Engine
{
public:
    Engine(int width, int height);
    int Init();
    bool Run();
    int Render();

    SDL_Surface* getScreen() { return screen; }

    void DrawPixel(SDL_Surface *screen, int x, int y, Uint8 R, Uint8 G, Uint8 B);
    void Slock(SDL_Surface *screen);
    void Sulock(SDL_Surface *screen);


private:
    SDL_Surface* screen;
    bool running;

    int width, height;
};

#endif // WINDOW_H
