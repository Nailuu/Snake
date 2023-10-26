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

int main(int argc, char** argv){
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_bool quit = SDL_FALSE;
    SDL_Event event;

    if(initWindow(&window, &renderer, WIDTH, HEIGHT) != 0)
        goto Quit;
    
    setIcon(window, getIcon("./sprite/icon2.bmp"));

    Snake *snake = initSnake();
    Apple *apple = initApple(WIDTH, HEIGHT);

    SDL_Texture *bgTexture = loadSprite("./sprite/tile.bmp", renderer);
    SDL_Texture *snakeTexture = loadSprite("./sprite/body.bmp", renderer);
    SDL_Texture *appleTexture = loadSprite("./sprite/apple.bmp", renderer);

    while(!quit)
    {
        // Logics
        newApple(apple);

        // Events
        SDL_WaitEventTimeout(&event, 250);
        if(event.type == SDL_QUIT)
        {
            printf("Closed after Quit Event");
            quit = SDL_TRUE;
            goto Quit;
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