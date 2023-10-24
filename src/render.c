#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include "../include/render.h"

int init(SDL_Window **window, SDL_Renderer **renderer, int width, int height)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "[ERROR] SDL_Init: %s", SDL_GetError());
        return -1;
    }

    if(SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_BORDERLESS, window, renderer) != 0)
    {
        fprintf(stderr, "[ERROR] SDL_CreateWindowAndRenderer: %s", SDL_GetError());
        return -1;
    }

    return 0;
}

int setWindowColor(SDL_Renderer *renderer, SDL_Color color)
{
    if(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) != 0)
    {
        fprintf(stderr, "[ERROR] SDL_SetRenderDrawColor: %s", SDL_GetError());
        return -1;
    }

    if(SDL_RenderClear(renderer) != 0)
    {
        fprintf(stderr, "[ERROR] SDL_RenderClear: %s", SDL_GetError());
        return -1;
    }
    
    return 0;
}