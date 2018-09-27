//
//  trapClass.cpp
//  SDL_Test
//
//  Created by MV Admin on 9/26/18.
//  Copyright © 2018 MV Admin. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "Header.h"
#include "SDL_Test/VectorClass.cpp"
#include "SDL_Test/main.cpp"

class SpikeTrap {
    private:
        int x;
        int y;
        double dir;
        int moveSpeed;
        SDL_Renderer *renderer;
    
    public:
        SpikeTrap(int startX, int startY, double startDir, SDL_Renderer *startRenderer, int movementSpeed = 5) {
            this->x = startX;
            this->y = startY;
            this->dir = startDir;
            this->moveSpeed = movementSpeed;
            this->renderer = startRenderer;
        }
    
        void move() {
//            if (this->vector.getX() > 0) {
//                this->vector.setX(this->vector.getX() - 1);
//            } else if (this->vector.getX() < 0) {
//                this->vector.setX(this->vector.getX() + 1);
//            }
//            
//            if (this->vector.getY() > 0) {
//                this->vector.setY(this->vector.getY() - 1);
//            } else if (this->vector.getX() < 0) {
//                this->vector.setY(this->vector.getY() + 1);
//            }
//            
//            this->x = this->vector.getX();
//            this->y = this->vector.getY();
            draw();
        }
    
        void draw() {
            renderIMGTexture(loadIMGTexture("pixel_trap.png", renderer), renderer, 0, 0, 0, 0);
        }
};