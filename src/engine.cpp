#include "engine.h"

Engine::Engine(int width, int height)
{
    this->width = width;
    this->height = height;

    running = false;

    startclock = 0;
    deltaclock = 0;
    raycount = 0;
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
        else if (Event.type == SDL_KEYDOWN)
        {
            if (Event.key.keysym.sym == SDLK_F11)
            {
                MakeScreenshot();
            }
        }
    }
    return true;
}

int Engine::Render()
{
    Slock(surface);

    // Отрисовка
    Screen::Result res;
    do
    {
        pixel px;
        res = screen->GetPixel(px);
        DrawPixel(surface, px.x, px.y, px.color.r, px.color.g, px.color.b);
        raycount++;
    } while (res == Screen::PixelDone);

    Sulock(surface);
    SDL_Flip(surface);

    deltaclock = SDL_GetTicks() - startclock;
    if (deltaclock >= 1000)
    {
        static char buffer[256] = {0};
        sprintf(buffer, "%d Rays Per Second", raycount);
        SDL_WM_SetCaption(buffer, 0);
        raycount = 0;
        deltaclock = 0;
        startclock = SDL_GetTicks();
    }
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

void Engine::MakeScreenshot()
{
    time_t seconds = time(NULL);
    char buffer[64];
    tm* timeinfo = localtime(&seconds);
    strftime(buffer, sizeof(buffer), "rTracer_%Y-%m-%d_%H-%M-%S.bmp", timeinfo);
    SDL_SaveBMP(surface, buffer);
}

