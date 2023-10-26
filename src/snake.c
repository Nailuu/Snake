#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/snake.h"

Snake *initSnake()
{
    Snake *snake = malloc(sizeof(snake));
    if(snake == NULL)
    {
        fprintf(stderr, "[ERROR] Initializing Snake Struct");
        exit(EXIT_FAILURE);
    }

    SnakeNode *head = malloc(sizeof(head));
    if(head == NULL)
    {
        fprintf(stderr, "[ERROR] Initializing Snake Head");
        exit(EXIT_FAILURE);
    }

    head->next = NULL;
    head->previous = NULL;
    head->x = 250;
    head->y = 0;
    head->direction = SOUTH;

    snake->head = head;
    snake->tail = head;
    snake->length = 1;
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
    SnakeNode *tail = malloc(sizeof(tail));
    if(tail == NULL)
    {
        fprintf(stderr, "[ERROR] Initializing Snake Tail");
        return -1;
    }

    tail->direction = snake->tail->direction;
    tail->next = NULL;
    tail->previous = snake->tail;
    tail->x = 0; // write function that calculate new tail coords based on old tail (+25 / -25)
    tail-> y = 0; // write function that calculate new tail coords based on old tail (+25 / -25)
    snake->tail->next = tail;
    snake->tail = tail;
    snake->length++;

    return 0;
}