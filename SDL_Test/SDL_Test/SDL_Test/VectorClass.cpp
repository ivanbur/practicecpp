//
//  VectorClass.cpp
//  SDL_Test
//
//  Created by MV Admin on 8/29/18.
//  Copyright © 2018 MV Admin. All rights reserved.
//

#include <stdio.h>
#include <math.h>

class Vector {
    private: int x;
    private: int y;
    private: double velocity;
    
    public: Vector(int startX, int startY) {
        this->x = startX;
        this->y = startY;
        updateVelocity();
    }
    
    private: void updateVelocity() {
        this->velocity = pow((pow(this->x, 2) + pow(this->y, 2)), (1/2));
    }
    
    public: Vector addVector(Vector vector) {
        int newX = this->x + vector.x;
        int newY = this->y + vector.y;
        
        return Vector(newX, newY);
    }
    
    public: Vector addVector(int x, int y) {
        int newX = this->x + x;
        int newY = this->y + y;
        
        return Vector(newX, newY);
    }
    
    public: Vector subtractVector(Vector vector) {
        int newX = this->x - vector.x;
        int newY = this->y - vector.y;
        
        return Vector(newX, newY);
    }
    
    public: void setX(int x) {
        this->x = x;
        updateVelocity();
    }
    
    public: void setY(int y) {
        this->y = y;
        updateVelocity();
    }
    
    public: int getX() {
        return this->x;
    }
    
    public: int getY() {
        return this->y;
    }
};