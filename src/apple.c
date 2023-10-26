#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/apple.h"

Apple *initApple()
{
    Apple *apple = (Apple*)malloc(1 * sizeof(Apple));
    if(apple == NULL)
    {
        fprintf(stderr, "[ERROR] Initializing apple");
        return NULL;
    }

    srand(time(NULL));
    apple->x = (rand() % 20) * 25;
    apple->y = (rand() % 20) * 25;
    printf("[LOG] Apple has appeared in x: %d / y: %d\n", apple->x, apple->y);

    return apple;
}

void destroyApple(Apple *apple)
{
    free(apple);
}

void newApple(Apple *apple)
{
    srand(time(NULL));
    apple->x = (rand() % 20) * 25;
    apple->y = (rand() % 20) * 25;
    printf("[LOG] Apple has appeared in x: %d / y: %d\n", apple->x, apple->y);
}