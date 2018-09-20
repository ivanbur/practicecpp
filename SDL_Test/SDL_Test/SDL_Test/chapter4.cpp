//
//  main.cpp
//  SDL_Test
//
//  Created by MV Admin on 7/11/18.
//  Copyright © 2018 MV Admin. All rights reserved.
//

#include "Header.h"
#include "VectorClass.cpp"


const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 720;
const int TILE_SIZE = 80;
const int TILE_SIZE_STONE = 48;
const int HEIGHT_STONE = TILE_SIZE_STONE*5;
const int CHARACTER_W = 91;
const int CHARACTER_H = 100;
const int CLIP_W = 48;
const int CLIP_H = 40;
const int FPS = 60;
const int MOVEMENT_SPEED = 2;

const int PLATFORM_LINE = SCREEN_HEIGHT - HEIGHT_STONE - CLIP_H;

bool pressedLeft = false;
bool pressedRight = false;
bool pressedUp = false;
bool pressedDown = false;

void movePlayer(int &xPos, int &yPos, Vector &playerVector) {
//    if (xPos + playerVector.getX() <= SCREEN_WIDTH - CHARACTER_W || xPos + playerVector.getX() >= 0) {
//        std::cout << xPos + playerVector.getX() << std::endl;
//        std::cout << SCREEN_WIDTH - CHARACTER_W << std::endl;
//        std::cout << playerVector.getX() << std::endl;
//        xPos += playerVector.getX();
//    } else {
//        std::cout << "testing" << std::endl;
//        if (xPos + playerVector.getX() > SCREEN_WIDTH) {
//            xPos = SCREEN_WIDTH;
//        } else {
//            xPos = 0;
//        }
//    }

    if (xPos < 0) {
        std::cout << "other stuff" << std::endl;
        playerVector.setX(10);
        xPos = 10;
    } else if(xPos > SCREEN_WIDTH - CLIP_W) {
        std::cout << "stuff" << std::endl;
        playerVector.setX(-10);
        xPos = SCREEN_WIDTH - CLIP_W - 10;
    } else {
        xPos += playerVector.getX();
    }
    
    yPos += playerVector.getY();
}

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
    
    if (IMG_Init(IMG_INIT_PNG) & (IMG_INIT_PNG != IMG_INIT_PNG)) { // Only initialize PNG cause that's all we're gonna use
        logSDLError(std::cout, "IMG_INIT_PNG");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    SDL_Event e;
    bool pressedQuit = false;
    
//    SDL_Texture *texture = loadIMGTexture("image.png", renderer);
//    SDL_Texture *character = loadIMGTexture("testingIMG.png", renderer);
    SDL_Texture *backgroundIMG = loadIMGTexture("pngGrassTile.png", renderer);
    SDL_Texture *backgroundStone = loadIMGTexture("stone_tile_big.png", renderer);
    SDL_Texture *backgroundSky = loadIMGTexture("backgroundSky.png", renderer);
    SDL_Texture *slime = loadIMGTexture("slime_sheet.png", renderer);
    SDL_Texture *trap = loadIMGTexture("pixel_trap.png", renderer);
    
    int XPos = SCREEN_WIDTH / 2 - CHARACTER_W / 2;
    int YPos = SCREEN_HEIGHT / 2 - CHARACTER_H / 2;
    int amountOfClipsSlime = 20;
    int currentClip = 0;
    int animateSlimeEveryXFrames = 8;
    int currentFrame = 0;
    bool facingRight = true;
    Vector playerVector = *new Vector(0, 0);
    Vector jumpVector = *new Vector(0, 5);
    Vector rightVector = *new Vector(MOVEMENT_SPEED, 0);
    Vector leftVector = *new Vector(-MOVEMENT_SPEED, 0);
    Vector gravityVector = *new Vector(0.0, -0.0);
    
    SDL_Rect allClips[amountOfClipsSlime];
    
    for (int i = 0; i < amountOfClipsSlime/2; i++) {
        allClips[i].x = 0;
        allClips[i].y = i*CLIP_H;
        allClips[i].w = CLIP_W;
        allClips[i].h = CLIP_H;
        
        int nextColumn = i + amountOfClipsSlime/2; // 2 is how many columns there are
        allClips[nextColumn].x = CLIP_W;
        allClips[nextColumn].y = allClips[i].y;
        allClips[nextColumn].w = CLIP_W;
        allClips[nextColumn].h = CLIP_H;
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
        
        if (pressedLeft) {
            facingRight = false;
            playerVector = playerVector.addVector(leftVector);
        }
        if (pressedRight) {
            facingRight = true;
            playerVector = playerVector.addVector(rightVector);
        }
        
        if (YPos <= PLATFORM_LINE) {
//            std::cout << currentFrame << std::endl;
            if (YPos + playerVector.subtractVector(gravityVector).getY() >= PLATFORM_LINE) {
                YPos = PLATFORM_LINE;
                gravityVector.setY(0);
                playerVector.setY(0);
            } else {
                playerVector = playerVector.subtractVector(gravityVector);
                gravityVector.setY(gravityVector.getY() - 0.85);
            }
        } else {
            gravityVector.setY(0);
            playerVector.setY(0);
        }
        if (pressedUp) {
            playerVector = playerVector.subtractVector(jumpVector);
        }


        if (playerVector.getX() > 0) {
            playerVector.setX(playerVector.getX() - 1);
        }
        
        if (playerVector.getX() < 0) {
            playerVector.setX(playerVector.getX() + 1);
        }
        
        movePlayer(XPos, YPos, playerVector);
        
        // Render
        SDL_RenderClear(renderer);
//        drawBackground(backgroundIMG, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, TILE_SIZE);
        renderIMGTexture(backgroundSky, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - 94);
        drawBackgroundFromBottom(backgroundStone, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, HEIGHT_STONE, TILE_SIZE_STONE);
//        renderIMGTexture(character, renderer, XPos, YPos, CHARACTER_W, CHARACTER_H);
        renderClipTexture(slime, renderer, XPos, YPos, &allClips[currentClip]);
        if (currentFrame % animateSlimeEveryXFrames == 0) {
            currentClip++;
        }
        currentClip %= amountOfClipsSlime/2;
        if (facingRight) {
            currentClip += amountOfClipsSlime/2;
        }
        
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
