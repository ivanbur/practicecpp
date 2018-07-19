//
//  main.cpp
//  SDL_Test
//
//  Created by MV Admin on 7/11/18.
//  Copyright © 2018 MV Admin. All rights reserved.
//

#include <iostream>
#include "SDL2/SDL.h"
#include "string"

void logSDLError(std::ostream &os, const std::string &msg);
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *renderer);

const int screenWidth = 1080;
const int screenHeight = 920;

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) { // should return 0 if all goes well
        logSDLError(std::cout, "SDL_INIT_VIDEO");
        return 1; // has to return something for main
    }
    
    SDL_Window *window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    
    if (window == nullptr) { // if something went wrong window should equal nullptr
        logSDLError(std::cout, "SDL_CreateWindow");
        SDL_Quit(); // clean up sdl before exiting program
        return 1;
    }
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if (renderer == nullptr) { // if something went wrong renderer should equal nullptr
        SDL_DestroyWindow(window); // have to clean up everything we've already made before exiting
        logSDLError(std::cout, "SDL_CreateRenderer");
        SDL_Quit();
        return 1;
    }
    
    SDL_Texture *texture = loadTexture("hello.bmp", renderer);
    
    
    SDL_RenderClear(renderer);
    
//    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    
    SDL_RenderPresent(renderer);
    
    SDL_Delay(3000);
    
    std::cout << "hello" << std::endl;
    
    // Clean up properly
    
    SDL_DestroyTexture(texture);
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
