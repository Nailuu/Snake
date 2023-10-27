#ifndef APPLE_H
#define APPLE_H

typedef struct Apple
{
    int x;
    int y;
} Apple;

Apple *initApple(Snake *snake);
void destroyApple(Apple *apple);
void newApple(Apple *apple, Snake *snake);

#endif