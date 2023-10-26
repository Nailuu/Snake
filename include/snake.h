#ifndef SNAKE_H
#define SNAKE_H

typedef enum
{
    n, s, e, w
} Direction;

typedef struct SnakeNode
{
    int x;
    int y;
    Direction direction;
    struct SnakeNode *next;
    struct SnakeNode *previous;
} SnakeNode;

typedef struct Snake
{
    SnakeNode *head;
    SnakeNode *tail;
    int length;
} Snake;

Snake *initSnake();
void destroySnake(Snake *snake);
int growSnake(Snake *snake);

#endif