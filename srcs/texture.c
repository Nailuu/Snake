#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include "texture.h"

SDL_Texture *loadSprite(char *path, SDL_Renderer *renderer)
{
    SDL_Surface *surface = NULL;
    SDL_Texture *texture, *tmp = NULL;

    surface = SDL_LoadBMP(path);
    if(surface == NULL)
    {
        fprintf(stderr, "[ERROR] SDL_LoadBMP: %s", SDL_GetError());
        return NULL;
    }
    
    tmp = SDL_CreateTextureFromSurface(renderer, surface);
    if(tmp == NULL)
    {
        fprintf(stderr, "[ERROR] SDL_CreateTextureFromSurface: %s", SDL_GetError());
        return NULL;
    }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, surface->w, surface->h);
    if(texture == NULL)
    {
        fprintf(stderr, "[ERROR] SDL_CreateTextureFromSurface: %s", SDL_GetError());
        return NULL;
    }

    SDL_SetRenderTarget(renderer, texture);
    SDL_RenderCopy(renderer, tmp, NULL, NULL);
    SDL_DestroyTexture(tmp);
    SDL_FreeSurface(surface);
    SDL_SetRenderTarget(renderer, NULL);
    return texture;
}

SDL_Surface *getIcon(char *path)
{
    SDL_Surface *surface = NULL;

    surface = SDL_LoadBMP(path);
    if(surface == NULL)
    {
        fprintf(stderr, "[ERROR] SDL_LoadBMP: %s", SDL_GetError());
        return NULL;
    }

    return surface;
}