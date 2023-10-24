#ifndef TEXTURE_H
#define TEXTURE_H

SDL_Texture *loadSprite(char *path, SDL_Renderer *renderer);
SDL_Surface *getIcon(char *path);

#endif