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
int getNewTailX(SnakeNode *tail, Direction direction);
int getNewTailY(SnakeNode *tail, Direction direction);
int growSnake(Snake *snake);
int isSnakeHere(int x, int y, Snake *snake);
void updateSnakeDirection(Snake *snake);
void updateDirection(Snake *snake, Direction newDirection);
int getUpdateSnakeNodeX(SnakeNode *node, Direction direction);
int getUpdateSnakeNodeY(SnakeNode *node, Direction direction);
void updateSnake(Snake *snake);

#endif