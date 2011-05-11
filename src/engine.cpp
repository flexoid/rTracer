#include "engine.h"

Engine::Engine(int width, int height)
{
    this->width = width;
    this->height = height;

    running = false;
}

int Engine::Init(Screen* screen)
{
    this->screen = screen;

    // Инициализация SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        return -1;
    }
    atexit(SDL_Quit);

    // Создаем поверхность для отрисовки
    surface = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE|SDL_DOUBLEBUF );

    //Проверяем, создалось ли окно
    if (surface == NULL)
    {
        printf("Unable to set %dx%d video: %s\n", width, height, SDL_GetError());
        return -1;
    }

    // Визуализация запущена
    running = true;
    return 0;
}

bool Engine::Run()
{
    SDL_Event Event;
    while(SDL_PollEvent(&Event))
    {
        if (Event.type == SDL_QUIT)
            return false;
    }
    return true;
}

int Engine::Render()
{
    Slock(surface);

    // Отрисовка
    pixel px = screen->GetPixel();
    DrawPixel(surface, px.x, px.y, px.color.r, px.color.g, px.color.b);

    Sulock(surface);
    SDL_Flip(surface);
}

void Engine::DrawPixel(SDL_Surface *screen, int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
    Uint32 color = SDL_MapRGB(screen->format, R, G, B);
    switch (screen->format->BytesPerPixel)
    {
    case 1: // Assuming 8-bpp
    {
        Uint8 *bufp;
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
        *bufp = color;
    }
        break;
    case 2: // Probably 15-bpp or 16-bpp
    {
        Uint16 *bufp;
        bufp = (Uint16 *)screen->pixels + y*screen->pitch/2 + x;
        *bufp = color;
    }
        break;
    case 3: // Slow 24-bpp mode, usually not used
    {
        Uint8 *bufp;
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x * 3;
        if(SDL_BYTEORDER == SDL_LIL_ENDIAN)
        {
            bufp[0] = color;
            bufp[1] = color >> 8;
            bufp[2] = color >> 16;
        } else {
            bufp[2] = color;
            bufp[1] = color >> 8;
            bufp[0] = color >> 16;
        }
    }
        break;
    case 4: // Probably 32-bpp
    {
        Uint32 *bufp;
        bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x;
        *bufp = color;
    }
        break;
    }
}

void Engine::Slock(SDL_Surface *screen)
{
    if ( SDL_MUSTLOCK(screen) )
    {
        if ( SDL_LockSurface(screen) < 0 )
        {
            return;
        }
    }
}

void Engine::Sulock(SDL_Surface *screen)
{
    if ( SDL_MUSTLOCK(screen) )
    {
        SDL_UnlockSurface(screen);
    }
}

