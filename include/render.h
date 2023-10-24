#ifndef RENDER_H
#define RENDER_H

int init(SDL_Window **window, SDL_Renderer **renderer, int width, int height);
int setWindowColor(SDL_Renderer *renderer, SDL_Color color);

#endif