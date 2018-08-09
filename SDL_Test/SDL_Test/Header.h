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

// SDL_Window *window;
// SDL_Renderer *renderer;


//const int TILE_SIZE = 80;
//const int SCREEN_WIDTH = 960;
//const int SCREEN_HEIGHT = 720;
//const int SECOND_CHARACTER_W = 91;
//const int SECOND_CHARACTER_H = 100;


void logSDLError(std::ostream &os, const std::string &msg);
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *renderer);
void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y);
void renderIMGTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h);
void renderIMGTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y);
SDL_Texture* loadIMGTexture(const std::string &file, SDL_Renderer *renderer);
void renderClipTexture(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Rect dst, SDL_Rect *clip = nullptr);
void renderClipTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, SDL_Rect *clip = nullptr);
void drawBackground(SDL_Texture *backgroundIMG, SDL_Renderer *renderer, int screenWidth, int screenHeight, int tileSize);

#endif /* Header_h */
