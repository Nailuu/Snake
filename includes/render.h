#ifndef RENDER_H
#define RENDER_H

int initWindow(SDL_Window **window, SDL_Renderer **renderer, int width, int height);
void setIcon(SDL_Window *window, SDL_Surface *surface);
int setWindowColor(SDL_Renderer *renderer, SDL_Color color);
int renderTileBackground(SDL_Renderer *renderer, SDL_Texture *texture, int width, int height);
int renderSnake(SDL_Renderer *renderer, SDL_Texture *texture, Snake *snake);
int renderApple(SDL_Renderer *renderer, SDL_Texture *texture, Apple *apple);
int renderFont(SDL_Renderer *renderer, TTF_Font *font, char *text, int x, int y);
int renderScoreFont(SDL_Renderer *renderer, TTF_Font *font);
int renderScoreFontValue(SDL_Renderer *renderer, TTF_Font *font, int score);

#endif