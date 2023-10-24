#ifndef RENDER_H
#define RENDER_H

int init(SDL_Window **window, SDL_Renderer **renderer, int width, int height);
int setIcon(SDL_Window *window, SDL_Surface *surface);
int setWindowColor(SDL_Renderer *renderer, SDL_Color color);
int renderTileBackground(SDL_Renderer *renderer, int width, int height);

#endif