#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include "../include/snake.h"
#include "../include/render.h"
#include "../include/texture.h"

int initWindow(SDL_Window **window, SDL_Renderer **renderer, int width, int height)
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

void setIcon(SDL_Window *window, SDL_Surface *surface)
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

int renderTileBackground(SDL_Renderer *renderer, SDL_Texture *texture, int width, int height)
{
    SDL_Rect dst = {0, 0, 0, 0};

    if(SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h) != 0)
    {
        fprintf(stderr, "[ERROR] SDL_QueryTexture: %s", SDL_GetError());
        return -1;
    }

    for(int i = 0; i < (width / 20); i++)
    {
        for(int j = 0; j < (height / 20); j++)
        {
            dst.x = (width / 20) * (i % 20);
            dst.y = (height / 20) * (j % 20);

            if(SDL_RenderCopy(renderer, texture, NULL, &dst) != 0)
            {
                fprintf(stderr, "[ERROR] SDL_RenderCopy: %s", SDL_GetError());
                return -1;
            }
        }
    }

    return 0;
}

int renderSnake(SDL_Renderer *renderer, SDL_Texture *texture, Snake *snake)
{
    SDL_Rect dst = {0, 0, 0, 0};

    if(SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h) != 0)
    {
        fprintf(stderr, "[ERROR] SDL_QueryTexture: %s", SDL_GetError());
        return -1;
    }

    SnakeNode *tmp = snake->head;
    for(int i = 0; i < snake->length; i++)
    {
        dst.x = tmp->x;
        dst.y = tmp->y;
        tmp = tmp->next;

        if(SDL_RenderCopy(renderer, texture, NULL, &dst) != 0)
        {
            fprintf(stderr, "[ERROR] SDL_RenderCopy: %s", SDL_GetError());
            return -1;
        }
    }

    return 0;
}