#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include "../include/render.h"
#include "../include/texture.h"
#include "../include/snake.h"

#define WIDTH 500 
#define HEIGHT 500

int main(int argc, char** argv){
    
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    SDL_bool quit = SDL_FALSE;
    SDL_Event event;

    SDL_Color purple = {218, 112, 214, 255};
    SDL_Color blue = {30, 144, 255, 255};
    SDL_Rect cube = {0, 0, 50, 50};

    // 0 = NORTH, 1 = SOUTH, 2 = EAST, 3 = WEST
    int direction = 1;

    if(initWindow(&window, &renderer, WIDTH, HEIGHT) != 0)
        goto Quit;

    Snake *snake = initSnake();
    if(growSnake(snake) != 0)
        goto Quit;

    if(growSnake(snake) != 0)
        goto Quit;

    if(growSnake(snake) != 0)
        goto Quit;

    destroySnake(snake);

    setIcon(window, getIcon("./sprite/icon2.bmp"));

    SDL_Texture *bgTexture = loadSprite("./sprite/tile.bmp", renderer);

    // if(setWindowColor(renderer, purple) != 0)
    //     goto Quit;

    // SDL_SetRenderDrawColor(renderer, blue.r, blue.g, blue.b, blue.a);

    while(!quit)
    {
        if(renderTileBackground(renderer, bgTexture, WIDTH, HEIGHT) != 0)
            goto Quit;

        // Listen to events
        SDL_WaitEventTimeout(&event, 250);
        if(event.type == SDL_QUIT)
        {
            printf("Closed after Quit Event");
            quit = SDL_TRUE;
            goto Quit;
        } 
        // else if(event.type == SDL_KEYDOWN)
        // {
        //     if(event.key.keysym.sym == SDLK_z)
        //     {
        //         direction = 0;
        //         // if(cube.y != 0)
        //         // {
        //         //     cube.y -= 10;
        //         // }
        //     }
        //     if(event.key.keysym.sym == SDLK_s)
        //     {
        //         direction = 1;
        //         // if(cube.y != (HEIGHT - cube.h))
        //         // {
        //         //     cube.y += 10;
        //         // }
        //     }
        //     if(event.key.keysym.sym == SDLK_q)
        //     {
        //         direction = 3;
        //         // if(cube.x != 0)
        //         // {
        //         //     cube.x -= 10;
        //         // }
        //     }
        //     if(event.key.keysym.sym == SDLK_d)
        //     {
        //         direction = 2;
        //         // if(cube.x != (WIDTH - cube.w))
        //         // {
        //         //     cube.x += 10;
        //         // }
        //     }
        // }
        // switch(direction)
        // {
        //     case 0:
        //         cube.y -= 50;
        //         break;
        //     case 1:
        //         cube.y += 50;
        //         break;
        //     case 2:
        //         cube.x += 50;
        //         break;
        //     case 3:
        //         cube.x -= 50;
        //         break;
        // }
        // SDL_Delay(250);

        // Render
        // setWindowColor(renderer, purple);
        // SDL_SetRenderDrawColor(renderer, blue.r, blue.g, blue.b, blue.a);
        // SDL_RenderFillRect(renderer, &cube);
        SDL_RenderPresent(renderer);
    }
    

    Quit:
    if(snake != NULL)
        destroySnake(snake);
    if(texture != NULL)
        SDL_DestroyTexture(texture);
    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if(window != NULL)
        SDL_DestroyWindow(window);
    SDL_Quit();
    exit(EXIT_FAILURE);
}