//
//  VectorClass.cpp
//  SDL_Test
//
//  Created by MV Admin on 8/29/18.
//  Copyright © 2018 MV Admin. All rights reserved.
//

#include <stdio.h>

class Vector {
    int x;
    int y;
    double angle;
    double velocity;
    
    Vector(int startX, int startY) {
        this->x = startX;
        this->y = startY;
    }
    
    void setAngle(double angle) {
        this->angle = angle;
    }
    
    void setVelocity(double velocity) {
        this->velocity = velocity;
    }
    
    void addVector(Vector vector) {
        int newX = this->x;
        int newY = this->y;
    }
};