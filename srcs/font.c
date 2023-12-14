#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void initFont(int size)
{
    TTF_Init();
    TTF_OpenFont("./assets/Silkscreen.ttf", size);
}