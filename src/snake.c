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
    node->x = 225;
    node->y = 300;
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

int getNewTailX(SnakeNode *tail, Direction direction)
{
    switch(direction)
    {
        case e:
            return (tail->x - 25);
        case w:
            return (tail->x + 25);
        default:
            return tail->x;
    }
}

int getNewTailY(SnakeNode *tail, Direction direction)
{
    switch(direction)
    {
        case n:
            return (tail->y + 25);
        case s:
            return (tail->y - 25);
        default:
            return tail->y;
    }
}

int growSnake(Snake *snake)
{

    SnakeNode *newTail = (SnakeNode*)malloc(1 * sizeof(SnakeNode));
    if(newTail == NULL)
    {
        fprintf(stderr, "[ERROR] Initializing Snake Tail");
        return -1;
    }

    newTail->direction = snake->tail->direction;
    newTail->next = NULL;
    newTail->previous = snake->tail;
    newTail->x = getNewTailX(newTail->previous, newTail->previous->direction);
    newTail->y = getNewTailY(newTail->previous, newTail->previous->direction);
    snake->tail->next = newTail;
    snake->tail = newTail;
    snake->length++;

    return 0;
}

int isSnakeHere(int x, int y, Snake *snake)
{
    SnakeNode *part = snake->head;
    while(part != NULL)
    {
        if(part->x == x && part->y == y)
        {
            return 1;
        }
        part = part->next;
    }
    
    return 0;
}

void updateSnakeDirection(Snake *snake)
{
    SnakeNode *part = snake->tail;
    while(part != NULL)
    {
        if(part->previous != NULL)
        {
            part->direction = part->previous->direction;
        }
        part = part->previous;
    }
}

void updateDirection(Snake *snake, Direction newDirection)
{
    snake->head->direction = newDirection;
}

int getUpdateSnakeNodeX(SnakeNode *node, Direction direction)
{
    switch(direction)
    {
        case e:
            return (node->x + 25);
        case w:
            return (node->x - 25);
        default:
            return node->x;
    }
}

int getUpdateSnakeNodeY(SnakeNode *node, Direction direction)
{
    switch(direction)
    {
        case n:
            return (node->y - 25);
        case s:
            return (node->y + 25);
        default:
            return node->y;
    }
}

void updateSnake(Snake *snake)
{
    SnakeNode *part = snake->head;
    while(part != NULL)
    {
        part->x = getUpdateSnakeNodeX(part, part->direction);
        part->y = getUpdateSnakeNodeY(part, part->direction);
        part = part->next;
    }

    updateSnakeDirection(snake);
}