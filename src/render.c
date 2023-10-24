#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include "../include/render.h"
#include "../include/texture.h"

int init(SDL_Window **window, SDL_Renderer **renderer, int width, int height)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "[ERROR] SDL_Init: %s", SDL_GetError());
        return -1;
    }

    if(SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, window, renderer) != 0)
    {
        fprintf(stderr, "[ERROR] SDL_CreateWindowAndRenderer: %s", SDL_GetError());
        return -1;
    }

    return 0;
}

int setIcon(SDL_Window *window, SDL_Surface *surface)
{
    SDL_SetWindowIcon(window, surface);
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

int renderTileBackground(SDL_Renderer *renderer, int width, int height)
{
    SDL_Texture *texture = NULL;
    texture = loadSprite("./sprite/tile.bmp", renderer);
    if(texture == NULL)
    {
        return -1;
    }

    SDL_Rect dst = {0, 0, 0, 0};

    SDL_SetRenderTarget(renderer, texture);
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);

    for(int i = 0; i < (width / 20); i++)
    {
        for(int j = 0; j < (height / 20); j++)
        {
            dst.x = (width / 20) * (i % 20);
            dst.y = (height / 20) * (j % 20);
            SDL_RenderCopy(renderer, texture, NULL, &dst);
        }
    }

    SDL_DestroyTexture(texture);
    SDL_SetRenderTarget(renderer, NULL);
}