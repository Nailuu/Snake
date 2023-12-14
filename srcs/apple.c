#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h"
#include "apple.h"

Apple *initApple(Snake *snake)
{
    Apple *apple = (Apple*)malloc(1 * sizeof(Apple));
    if(apple == NULL)
    {
        fprintf(stderr, "[ERROR] Initializing apple");
        return NULL;
    }

    srand(time(NULL));

    // Avoid apple from spawning on the snake
    do {
        apple->x = (rand() % 20) * 25;
        apple->y = (rand() % 20) * 25;
    } while(isSnakeHere(apple->x, apple->y, snake) != 0);
    
    //printf("[LOG] Apple has appeared in x: %d / y: %d\n", apple->x, apple->y);

    return apple;
}

void destroyApple(Apple *apple)
{
    free(apple);
}

// Create function to check if apple is not on the snake
void newApple(Apple *apple, Snake *snake)
{
    srand(time(NULL));

    // Avoid apple from spawning on the snake
    do {
        apple->x = (rand() % 20) * 25;
        apple->y = (rand() % 20) * 25;
    } while(isSnakeHere(apple->x, apple->y, snake) != 0);

    //printf("[LOG] Apple has appeared in x: %d / y: %d\n", apple->x, apple->y);
}

void isAppleEaten(Apple *apple, Snake *snake, int *score)
{
    if(snake->head->x == apple->x && snake->head->y == apple->y)
    {
        growSnake(snake, score);
        newApple(apple, snake);
    }
}