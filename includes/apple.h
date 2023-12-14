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
void isAppleEaten(Apple *apple, Snake *snake, int *score);

#endif