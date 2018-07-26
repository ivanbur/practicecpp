//
//  main.cpp
//  SDL_Test
//
//  Created by MV Admin on 7/11/18.
//  Copyright © 2018 MV Admin. All rights reserved.
//

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "string"

void logSDLError(std::ostream &os, const std::string &msg);
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *renderer);
void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y);
void renderIMGTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h);
void renderIMGTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y);
SDL_Texture* loadIMGTexture(const std::string &file, SDL_Renderer *renderer);

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int TILE_SIZE = 60;

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) { // should return 0 if all goes well
        logSDLError(std::cout, "SDL_INIT_VIDEO");
        return 1; // has to return something for main
    }
    
    SDL_Window *window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    if (window == nullptr) { // if something went wrong window should equal nullptr
        logSDLError(std::cout, "SDL_CreateWindow");
        SDL_Quit(); // clean up sdl before exiting program
        return 1;
    }
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if (renderer == nullptr) { // if something went wrong renderer should equal nullptr
        logSDLError(std::cout, "SDL_CreateRenderer");
        SDL_DestroyWindow(window); // have to clean up everything we've already made before exiting
        SDL_Quit();
        return 1;
    }
    
//    SDL_Texture *texture = loadTexture("hello.bmp", renderer);
//    SDL_Texture *sonicTexture = loadTexture("pixelsonic.bmp", renderer);
//    SDL_Texture *background = loadTexture("background.bmp", renderer);
//    
//    if (background == nullptr || sonicTexture == nullptr) {
//        logSDLError(std::cout, "loadTexture");
//        SDL_DestroyRenderer(renderer);
//        SDL_DestroyWindow(window);
//        SDL_Quit();
//        return 1;
//    }
//    
    SDL_RenderClear(renderer);
    
    if (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG != IMG_INIT_PNG) { // Only initialize PNG cause that's all we're gonna use
        logSDLError(std::cout, "IMG_INIT_PNG");
        SDL_Quit();
        return 1;
    }
    
//    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    
//    int sonicW, sonicH;
//    
//    SDL_QueryTexture(sonicTexture, NULL, NULL, &sonicW, &sonicH);
//    int x = (SCREEN_WIDTH / 2 - sonicW / 2);
//    int y = (SCREEN_HEIGHT / 2 - sonicH / 2) + 25;
//    
//    renderTexture(background, renderer, 0, 0);
//    
//    renderTexture(sonicTexture, renderer, x, y);
//    
//    SDL_RenderPresent(renderer);
//    
    
//
    std::cout << "debug" << std::endl;
    
    // loading textures
    
    SDL_Texture *secondBackground = loadIMGTexture("pngGrassTile.png", renderer);
    SDL_Texture *secondCharacter = loadIMGTexture("testingIMG.png", renderer);
    
    if (secondBackground == nullptr || secondCharacter == nullptr) {
        logSDLError(std::cout, "loadIMGTexture");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
    
    // Draw tiles
    
    int xTiles = SCREEN_WIDTH / TILE_SIZE;
    int yTiles = SCREEN_HEIGHT / TILE_SIZE;
    
    for (int i = 0; i < xTiles * yTiles; i++) {
        int tileX = i % xTiles;
        int tileY = i % yTiles;
        renderIMGTexture(secondBackground, renderer, tileX * TILE_SIZE, tileY * TILE_SIZE, TILE_SIZE, TILE_SIZE);
    }
    
    // Draw character
    
    renderIMGTexture(secondCharacter, renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    
    SDL_RenderPresent(renderer);
    SDL_Delay(10000);
    
    // Clean up properly
    
    SDL_DestroyTexture(secondCharacter);
    SDL_DestroyTexture(secondBackground);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}

void logSDLError(std::ostream &os, const std::string &msg) {
    os << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *renderer) {
    SDL_Surface *surface = SDL_LoadBMP(file.c_str());
    
    SDL_Texture *texture = nullptr; // start as nullpointer to avoid pointer errors
    
    if (surface != nullptr) { // if it loaded ok
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        
        if (texture == nullptr) { // if didn't load ok
            logSDLError(std::cout, "SDL_CreateTextureFromSurface");
        }
    } else {
        logSDLError(std::cout, "SDL_LoadBMP");
    }
    
    return texture;
}

// SDL_Image loadtexture

SDL_Texture* loadIMGTexture(const std::string &file, SDL_Renderer *renderer) {
    SDL_Texture *texture = IMG_LoadTexture(renderer, file.c_str());
    if (texture == nullptr) {
        logSDLError(std::cout, "IMG_LoadTexture");
    }
    
    return texture;
}

void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y) {
    // Set up destination rectangle
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    
    // Query texture to get width & height to use
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(renderer, texture, NULL, &dst);
}

void renderIMGTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h) {
    SDL_Rect dst; // destination rectangle
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
    
    SDL_RenderCopy(renderer, texture, NULL, &dst);
}

void renderIMGTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y) {
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    renderIMGTexture(texture, renderer, x, y, w, h);
}
