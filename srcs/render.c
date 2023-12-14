#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "snake.h"
#include "apple.h"
#include "render.h"
#include "texture.h"

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

int renderApple(SDL_Renderer *renderer, SDL_Texture *texture, Apple *apple)
{
    SDL_Rect dst = {0, 0, 0, 0};

    if(SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h) != 0)
    {
        fprintf(stderr, "[ERROR] SDL_QueryTexture: %s", SDL_GetError());
        return -1;
    }

    dst.x = apple->x;
    dst.y = apple->y;
    
    if(SDL_RenderCopy(renderer, texture, NULL, &dst) != 0)
    {
        fprintf(stderr, "[ERROR] SDL_RenderCopy: %s", SDL_GetError());
        return -1;
    }

    return 0;
}

int renderFont(SDL_Renderer *renderer, TTF_Font *font, char *text, int x, int y)
{
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface *tmp = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *textImg = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_Rect dst = {x, y, tmp->w, tmp->h};
    SDL_FreeSurface(tmp);
    if(SDL_RenderCopy(renderer, textImg, NULL, &dst) != 0)
    {
        fprintf(stderr, "[ERROR] SDL_RenderCopy: %s", SDL_GetError());
        return -1;
    }
    return 0;
}

int renderScoreFont(SDL_Renderer *renderer, TTF_Font *font)
{
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface *tmp = TTF_RenderText_Solid(font, "Score:", color);
    SDL_Texture *textImg = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_Rect dst = {15, 465, tmp->w, tmp->h};
    SDL_FreeSurface(tmp);
    if(SDL_RenderCopy(renderer, textImg, NULL, &dst) != 0)
    {
        fprintf(stderr, "[ERROR] SDL_RenderCopy: %s", SDL_GetError());
        return -1;
    }
    return 0;
}

int renderScoreFontValue(SDL_Renderer *renderer, TTF_Font *font, int score)
{
    int length = floor(log10(abs(score))) + 1;
    char *str = NULL;
    str = (char *)malloc(sizeof(char) * (length + 1));
    str[length] = '\0';
    SDL_Color color = {51, 153, 255, 255};
    SDL_Surface *tmp = TTF_RenderText_Solid(font, itoa(score, str, 10), color);
    free(str);
    SDL_Texture *textImg = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_Rect dst = {100, 465, tmp->w, tmp->h};
    SDL_FreeSurface(tmp);
    if(SDL_RenderCopy(renderer, textImg, NULL, &dst) != 0)
    {
        fprintf(stderr, "[ERROR] SDL_RenderCopy: %s", SDL_GetError());
        return -1;
    }
    return 0;
}