#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/snake.h"

Snake *initSnake()
{
    Snake *snake = (Snake*)malloc(1 * sizeof(Snake));
    if(snake == NULL)
    {
        fprintf(stderr, "[ERROR] Initializing Snake Struct");
        return NULL;
    }

    SnakeNode *node = (SnakeNode*)malloc(1 * sizeof(SnakeNode));
    if(node == NULL)
    {
        fprintf(stderr, "[ERROR] Initializing Snake Head");
        return NULL;
    }

    node->next = NULL;
    node->previous = NULL;
    node->x = 250;
    node->y = 250;
    node->direction = s;

    snake->head = node;
    snake->tail = node;
    snake->length = 1;

    return snake;
}

void destroySnake(Snake *snake)
{
    if(snake->length == 1)
    {
        free(snake->head);
        free(snake);
        return;
    }

    SnakeNode *tmp = snake->tail;
    while(tmp->previous != NULL)
    {
        tmp = tmp->previous;
        free(tmp->next);
    }

    free(tmp);
    free(snake);
}

int growSnake(Snake *snake)
{

    SnakeNode *tail = (SnakeNode*)malloc(1 * sizeof(SnakeNode));
    if(tail == NULL)
    {
        fprintf(stderr, "[ERROR] Initializing Snake Tail");
        return -1;
    }

    tail->direction = snake->tail->direction;
    tail->next = NULL;
    tail->previous = snake->tail;
    tail->x = tail->previous->x; // write function that calculate new tail coords based on old tail (+25 / -25)
    tail-> y = tail->previous->y - 25; // write function that calculate new tail coords based on old tail (+25 / -25)
    snake->tail->next = tail;
    snake->tail = tail;
    snake->length++;

    return 0;
}