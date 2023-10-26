#ifndef SNAKE_H
#define SNAKE_H

typedef enum DIRECTION DIRECTION;
enum DIRECTION
{
    NORTH,
    SOUTH,
    EAST,
    WEST
};

typedef struct SnakeNode SnakeNode;
struct SnakeNode
{
    int x;
    int y;
    DIRECTION direction;
    SnakeNode *next;
    SnakeNode *previous;
};

typedef struct Snake Snake;
struct Snake
{
    SnakeNode *head;
    SnakeNode *tail;
    int length;
};

Snake *initSnake();
void destroySnake(Snake *snake);
int growSnake(Snake *snake);

#endif