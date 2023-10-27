#include <crtdbg.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include "../include/snake.h"
#include "../include/apple.h"
#include "../include/render.h"
#include "../include/texture.h"

#define WIDTH 500 
#define HEIGHT 500
#define FPS 5

int main(int argc, char** argv){
    int lastUpdate = SDL_GetTicks();

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_bool quit = SDL_FALSE;
    SDL_Event event;

    if(initWindow(&window, &renderer, WIDTH, HEIGHT) != 0)
        goto Quit;
    
    setIcon(window, getIcon("./sprite/icon2.bmp"));

    Snake *snake = initSnake();
    Apple *apple = initApple(snake);
    growSnake(snake);
    growSnake(snake);
    growSnake(snake);
    growSnake(snake);
    growSnake(snake);

    SDL_Texture *bgTexture = loadSprite("./sprite/tile.bmp", renderer);
    SDL_Texture *snakeTexture = loadSprite("./sprite/snake.bmp", renderer);
    SDL_Texture *appleTexture = loadSprite("./sprite/apple.bmp", renderer);

    while(!quit)
    {
        // Events
        SDL_PollEvent(&event);
        if(event.type == SDL_QUIT)
        {
            printf("Closed after Quit Event");
            quit = SDL_TRUE;
            goto Quit;
        } else if(event.type == SDL_KEYDOWN)
        {
            if(event.key.keysym.scancode == SDL_SCANCODE_A)
            {
                updateDirection(snake, w);
            }
            else if(event.key.keysym.scancode == SDL_SCANCODE_D)
            {
                updateDirection(snake, e);
            }
            else if(event.key.keysym.scancode == SDL_SCANCODE_W)
            {
                updateDirection(snake, n);
            }
            else if(event.key.keysym.scancode == SDL_SCANCODE_S)
            {
                updateDirection(snake, s);
            }
            
        }

        // Logics
        int current = SDL_GetTicks();
        if((current - lastUpdate) > 1000 / FPS)
        {
            updateSnake(snake);
            lastUpdate = current;
        }
    
        // Render
        SDL_RenderClear(renderer);
        if(renderTileBackground(renderer, bgTexture, WIDTH, HEIGHT) != 0)
            goto Quit;

        if(renderSnake(renderer, snakeTexture, snake) != 0)
            goto Quit;

        if(renderApple(renderer, appleTexture, apple) != 0)
            goto Quit;

        SDL_RenderPresent(renderer);

        // int end = SDL_GetPerformanceCounter();
        // float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

        // SDL_Delay(floor(200.000f - elapsedMS));
    }


    Quit:
    if(snake != NULL)
        destroySnake(snake);
    if(apple != NULL)
        destroyApple(apple);
    if(appleTexture != NULL)
        SDL_DestroyTexture(appleTexture);
    if(snakeTexture != NULL)
        SDL_DestroyTexture(snakeTexture);
    if(bgTexture != NULL)
        SDL_DestroyTexture(bgTexture);
    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if(window != NULL)
        SDL_DestroyWindow(window);
    SDL_Quit();
    exit(EXIT_FAILURE);
}