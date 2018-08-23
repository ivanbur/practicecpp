//
//  main.cpp
//  SDL_Test
//
//  Created by MV Admin on 7/11/18.
//  Copyright © 2018 MV Admin. All rights reserved.
//

#include "Header.h"


const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 720;
const int TILE_SIZE = 80;
const int CHARACTER_W = 91;
const int CHARACTER_H = 100;
const int FPS = 60;

bool pressedLeft = false;
bool pressedRight = false;
bool pressedUp = false;
bool pressedDown = false;

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) { // should return 0 if all goes well
        logSDLError(std::cout, "SDL_INIT_VIDEO");
        return 1; // has to return something for main
    }
    
    SDL_Window *window = SDL_CreateWindow("Ivan's Testing Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
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
    
    if (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG != IMG_INIT_PNG) { // Only initialize PNG cause that's all we're gonna use
        logSDLError(std::cout, "IMG_INIT_PNG");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    SDL_Event e;
    bool pressedQuit = false;
    
    SDL_Texture *texture = loadIMGTexture("image.png", renderer);
    SDL_Texture *character = loadIMGTexture("testingIMG.png", renderer);
    SDL_Texture *backgroundIMG = loadIMGTexture("pngGrassTile.png", renderer);
    SDL_Texture *slime = loadIMGTexture("slime_sheet.png", renderer);
    
    int clipWidth = 48;
    int clipHeight = 40;
    int XPos = SCREEN_WIDTH / 2 - CHARACTER_W / 2;
    int YPos = SCREEN_HEIGHT / 2 - CHARACTER_H / 2;
    int amountOfClips = 10;
    int currentClip = 0;
    int animateSlimeEveryXFrames = 8;
    int currentFrame = 0;
    
    SDL_Rect allClips[amountOfClips];
    
    for (int i = 0; i < amountOfClips; i++) {
        allClips[i].x = 0;
        allClips[i].y = i*clipHeight;
        allClips[i].w = clipWidth;
        allClips[i].h = clipHeight;
    }
    
    while(!pressedQuit) {
        while (SDL_PollEvent(&e)) {
            
            if (e.type == SDL_QUIT) { // Closed window manually
                pressedQuit = true;
            }
            if (e.type == SDL_KEYDOWN) { // Pressed key
                switch(e.key.keysym.sym) {
                    case SDLK_UP:
                        pressedUp = true;
                        break;
                    case SDLK_DOWN:
                        pressedDown = true;
                        break;
                    case SDLK_LEFT:
                        pressedLeft = true;
                        break;
                    case SDLK_RIGHT:
                        pressedRight = true;
                        break;
                    case SDLK_ESCAPE:
                        pressedQuit = true;
                        break;
                    default:
                        break;
                }
            }
            if (e.type == SDL_KEYUP) {
                switch(e.key.keysym.sym) {
                    case SDLK_UP:
                        pressedUp = false;
                        break;
                    case SDLK_DOWN:
                        pressedDown = false;
                        break;
                    case SDLK_LEFT:
                        pressedLeft = false;
                        break;
                    case SDLK_RIGHT:
                        pressedRight = false;
                        break;
                    default:
                        break;
                }
            }
        }
        
        if (pressedUp) {
            YPos -= 10;
        }
        if (pressedDown) {
            YPos += 10;
        }
        if (pressedLeft) {
            XPos -= 10;
        }
        if (pressedRight) {
            XPos += 10;
        }

        
        // Render
        SDL_RenderClear(renderer);
        drawBackground(backgroundIMG, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, TILE_SIZE);
//        renderIMGTexture(character, renderer, XPos, YPos, CHARACTER_W, CHARACTER_H);
        renderClipTexture(slime, renderer, XPos, YPos, &allClips[currentClip]);
        if (currentFrame % animateSlimeEveryXFrames == 0) {
            currentClip++;
        }
        currentClip %= amountOfClips;
        SDL_RenderPresent(renderer);
        SDL_Delay(1000*1/FPS);
        currentFrame++;
    }
    
    // Clean up properly
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit(); 
    SDL_Quit();
    
    return 0;
}
