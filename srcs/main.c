#include <crtdbg.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include "snake.h"
#include "apple.h"
#include "render.h"
#include "texture.h"
#include "font.h"

#define WIDTH 500 
#define HEIGHT 500
#define FPS 8

int main(int argc, char *argv[]) {
    argc += 0;
    argv += 0;
    int lastUpdate = SDL_GetTicks();

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    TTF_Font *font = NULL;
    TTF_Font *fontScore = NULL;
    SDL_bool quit = SDL_FALSE;
    int gameover = 0;
    int score = 1;
    SDL_Event event;

    if(initWindow(&window, &renderer, WIDTH, HEIGHT) != 0)
        goto Quit;
    
    font = initFont(50);
    fontScore = initFont(20);
    
    setIcon(window, getIcon("./assets/apple.bmp"));

    Snake *snake = initSnake(&score);
    Apple *apple = initApple(snake);

    SDL_Texture *bgTexture = loadSprite("./assets/tile.bmp", renderer);
    SDL_Texture *snakeTexture = loadSprite("./assets/snake.bmp", renderer);
    SDL_Texture *deadSnakeTexture = loadSprite("./assets/dead_snake.bmp", renderer);
    SDL_Texture *appleTexture = loadSprite("./assets/apple.bmp", renderer);

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
            // WRITE FUNCTOIN TO AVOID PRESSING FAST 2 DIRECTION CHANGE AND BEING INSIDE SNAKE
            if(event.key.keysym.scancode == SDL_SCANCODE_A)
            {
                if(snake->head->direction != e)
                    updateDirection(snake, w);
            }
            else if(event.key.keysym.scancode == SDL_SCANCODE_D)
            {
                if(snake->head->direction != w)
                    updateDirection(snake, e);
            }
            else if(event.key.keysym.scancode == SDL_SCANCODE_W)
            {
                if(snake->head->direction != s)
                    updateDirection(snake, n);
            }
            else if(event.key.keysym.scancode == SDL_SCANCODE_S)
            {
                if(snake->head->direction != n)
                    updateDirection(snake, s);
            }
            else if(gameover == 1 && event.key.keysym.scancode == SDL_SCANCODE_R)
            {
                gameover = 0;
                score = 1;
                destroySnake(snake);
                destroyApple(apple);
                snake = initSnake(&score);
                apple = initApple(snake);
            }
            
        }

        // Limit logic to a certain fps rate
        int current = SDL_GetTicks();
        if((current - lastUpdate) > (float)1000 / FPS && gameover != 1)
        {
            // Logics
            updateSnake(snake, &gameover);
            isAppleEaten(apple, snake, &score);
            lastUpdate = current;
        }
    
        // Render
        SDL_RenderClear(renderer);
        if(renderTileBackground(renderer, bgTexture, WIDTH, HEIGHT) != 0)
            goto Quit;

        if(gameover != 1)
        {
            if(renderSnake(renderer, snakeTexture, snake) != 0)
                goto Quit;
        } else {
            if(renderSnake(renderer, deadSnakeTexture, snake) != 0)
                goto Quit;
        }

        if(renderApple(renderer, appleTexture, apple) != 0)
            goto Quit;

        if(gameover == 1)
        {
            if(renderFont(renderer, font, "GAME OVER!", 75, 175) != 0)
                goto Quit;
            if(renderFont(renderer, fontScore, "Press R key to restart", 100, 250) != 0)
                goto Quit;
        }

        if(renderScoreFont(renderer, fontScore) != 0)
            goto Quit;

        if(renderScoreFontValue(renderer, fontScore, score) != 0)
            goto Quit;

        SDL_RenderPresent(renderer);
    }


    Quit:
    TTF_CloseFont(font);
    TTF_CloseFont(fontScore);
    if(snake != NULL)
        destroySnake(snake);
    if(apple != NULL)
        destroyApple(apple);
    if(appleTexture != NULL)
        SDL_DestroyTexture(appleTexture);
    if(snakeTexture != NULL)
        SDL_DestroyTexture(snakeTexture);
    if(deadSnakeTexture != NULL)
        SDL_DestroyTexture(deadSnakeTexture);
    if(bgTexture != NULL)
        SDL_DestroyTexture(bgTexture);
    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if(window != NULL)
        SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
    return 0;
}