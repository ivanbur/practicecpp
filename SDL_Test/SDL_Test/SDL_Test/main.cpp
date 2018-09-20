////
////  main.cpp
////  SDL_Test
////
////  Created by MV Admin on 7/11/18.
////  Copyright © 2018 MV Admin. All rights reserved.
////
//
//
#include "Header.h"
//
//const int TILE_SIZE = 80;
//const int SCREEN_WIDTH = 960;
//const int SCREEN_HEIGHT = 720;
//const int SECOND_CHARACTER_W = 91;
//const int SECOND_CHARACTER_H = 100;
//
//int main() {
//    
//    
//    if (SDL_Init(SDL_INIT_VIDEO) != 0) { // should return 0 if all goes well
//        logSDLError(std::cout, "SDL_INIT_VIDEO");
//        return 1; // has to return something for main
//    }
//    
//    SDL_Window *window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//    
//    if (window == nullptr) { // if something went wrong window should equal nullptr
//        logSDLError(std::cout, "SDL_CreateWindow");
//        SDL_Quit(); // clean up sdl before exiting program
//        return 1;
//    }
//    
//    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//    
//    if (renderer == nullptr) { // if something went wrong renderer should equal nullptr
//        logSDLError(std::cout, "SDL_CreateRenderer");
//        SDL_DestroyWindow(window); // have to clean up everything we've already made before exiting
//        SDL_Quit();
//        return 1;
//    }
//    
////    SDL_Texture *texture = loadTexture("hello.bmp", renderer);
////    SDL_Texture *sonicTexture = loadTexture("pixelsonic.bmp", renderer);
////    SDL_Texture *background = loadTexture("background.bmp", renderer);
////    
////    if (background == nullptr || sonicTexture == nullptr) {
////        logSDLError(std::cout, "loadTexture");
////        SDL_DestroyRenderer(renderer);
////        SDL_DestroyWindow(window);
////        SDL_Quit();
////        return 1;
////    }
////    
//    SDL_RenderClear(renderer);
//    
//    if (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG != IMG_INIT_PNG) { // Only initialize PNG cause that's all we're gonna use
//        logSDLError(std::cout, "IMG_INIT_PNG");
//        SDL_DestroyWindow(window);
//        SDL_Quit();
//        return 1;
//    }
//    
////    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
//    
////    int sonicW, sonicH;
////    
////    SDL_QueryTexture(sonicTexture, NULL, NULL, &sonicW, &sonicH);
////    int x = (SCREEN_WIDTH / 2 - sonicW / 2);
////    int y = (SCREEN_HEIGHT / 2 - sonicH / 2) + 25;
////    
////    renderTexture(background, renderer, 0, 0);
////    
////    renderTexture(sonicTexture, renderer, x, y);
////    
////    SDL_RenderPresent(renderer);
//    
//    // loading textures
//    
//    SDL_Texture *secondBackground = loadIMGTexture("pngGrassTile.png", renderer);
//    SDL_Texture *secondCharacter = loadIMGTexture("testingIMG.png", renderer);
//    
//    if (secondBackground == nullptr || secondCharacter == nullptr) {
//        logSDLError(std::cout, "loadIMGTexture");
//        SDL_DestroyRenderer(renderer);
//        SDL_DestroyWindow(window);
//        IMG_Quit();
//        SDL_Quit();
//        return 1;
//    }
//    
//    // Draw tiles
//    
//    int xTiles = SCREEN_WIDTH / TILE_SIZE;
//    int yTiles = SCREEN_HEIGHT / TILE_SIZE;
//    
//    std::cout << SCREEN_WIDTH % TILE_SIZE << " and " << xTiles << std::endl;
//    std::cout << SCREEN_HEIGHT % TILE_SIZE << " and " << yTiles << std::endl;
//    
//    int tileX = 0;
//    int tileY = 0;
//    
//    for (int i = 0; i < xTiles * yTiles; i++) {
//        renderIMGTexture(secondBackground, renderer, tileX * TILE_SIZE, tileY * TILE_SIZE, TILE_SIZE, TILE_SIZE);
//        
//        if (tileX < xTiles - 1) {
//            tileX++;
//        } else {
//            tileX = 0;
//            tileY++;
//        }
//        
//    }
//    
//    // Draw character
//    
//    renderIMGTexture(secondCharacter, renderer, (SCREEN_WIDTH / 2) - (SECOND_CHARACTER_W / 2), (SCREEN_HEIGHT / 2 - SECOND_CHARACTER_H / 2), SECOND_CHARACTER_W, SECOND_CHARACTER_H);
//    
//    SDL_RenderPresent(renderer);
//    SDL_Delay(10000);
//    
//    // Clean up properly
//    
//    SDL_DestroyTexture(secondCharacter);
//    SDL_DestroyTexture(secondBackground);
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    IMG_Quit(); 
//    SDL_Quit();
//    
////    chapter4();
//    
//    return 0;
//}

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

void renderClipTexture(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Rect dst, SDL_Rect *clip) {
    SDL_RenderCopy(renderer, texture, clip, &dst);
}

void renderClipTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, SDL_Rect *clip) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    
    if (clip != nullptr) {
        dst.w = clip->w;
        dst.h = clip->h;
    } else {
        SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    }
    
    renderClipTexture(texture, renderer, dst, clip);
}

void drawBackground(SDL_Texture *backgroundIMG, SDL_Renderer *renderer, int screenWidth, int screenHeight, int tileSize) {
    // Draw tiles
    
    int xTiles = screenWidth / tileSize;
    int yTiles = screenHeight / tileSize;
    
    int tileX = 0;
    int tileY = 0;
    
    for (int i = 0; i < xTiles * yTiles; i++) {
        renderIMGTexture(backgroundIMG, renderer, tileX * tileSize, tileY * tileSize, tileSize, tileSize);
    
        if (tileX < xTiles - 1) {
            tileX++;
        } else {
            tileX = 0;
            tileY++;
        }
            
    }

}

void drawBackgroundFromBottom(SDL_Texture *backgroundIMG, SDL_Renderer *renderer, int screenWidth, int screenHeight, int heightOfTilesWantToDraw, int tileSize) {
    // Draw tiles
    
    int xTiles = screenWidth / tileSize;
    int yTiles = heightOfTilesWantToDraw / tileSize;
    
    int tileX = 0;
    int tileY = (screenHeight - tileSize) / tileSize;
    
    for (int i = 0; i < xTiles * yTiles; i++) {
        renderIMGTexture(backgroundIMG, renderer, tileX * tileSize, tileY * tileSize, tileSize, tileSize);
        
        if (tileX < xTiles - 1) {
            tileX++;
        } else {
            tileX = 0;
            tileY--;
        }
        
    }
    
}

