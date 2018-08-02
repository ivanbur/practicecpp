//
//  Header.h
//  SDL_Test
//
//  Created by MV Admin on 8/1/18.
//  Copyright © 2018 MV Admin. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "string"

SDL_Window *window;
SDL_Renderer *renderer;

void logSDLError(std::ostream &os, const std::string &msg);
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *renderer);
void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y);
void renderIMGTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h);
void renderIMGTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y);
SDL_Texture* loadIMGTexture(const std::string &file, SDL_Renderer *renderer);


#endif /* Header_h */
