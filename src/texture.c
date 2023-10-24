#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include "../include/texture.h"

SDL_Texture *loadSprite(char *path, SDL_Renderer *renderer)
{
    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;

    surface = SDL_LoadBMP(path);
    if(surface == NULL)
    {
        fprintf(stderr, "[ERROR] SDL_LoadBMP: %s", SDL_GetError());
        return NULL;
    }
    
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(texture == NULL)
    {
        fprintf(stderr, "[ERROR] SDL_CreateTextureFromSurface: %s", SDL_GetError());
        return NULL;
    }

    SDL_FreeSurface(surface);
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