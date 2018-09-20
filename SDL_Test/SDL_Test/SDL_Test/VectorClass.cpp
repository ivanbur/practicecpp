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
    private: double x;
    private: double y;
    private: double velocity;
    
    public: Vector(int startX, int startY) {
        this->x = startX;
        this->y = startY;
        updateVelocity();
    }
    
    public: Vector(double startX, double startY) {
        this->x = startX;
        this->y = startY;
        updateVelocity();
    }
    
    private: void updateVelocity() {
        this->velocity = pow((pow(this->x, 2) + pow(this->y, 2)), (1/2));
    }
    
    public: Vector addVector(Vector vector) {
        double newX = this->x + vector.x;
        double newY = this->y + vector.y;
        
        return Vector(newX, newY);
    }
    
    public: Vector addVector(int x, int y) {
        double newX = this->x + x;
        double newY = this->y + y;
        
        return Vector(newX, newY);
    }
    
    public: Vector addVector(double x, double y) {
        double newX = this->x + x;
        double newY = this->y + y;
    
        return Vector(newX, newY);
    }
    
    public: Vector subtractVector(Vector vector) {
        double newX = this->x - vector.x;
        double newY = this->y - vector.y;
        
        return Vector(newX, newY);
    }
    
    public: void setX(int x) {
        this->x = x;
        updateVelocity();
    }
    
    public: void setX(double x) {
        this->x = x;
        updateVelocity();
    }
    
    public: void setY(int y) {
        this->y = y;
        updateVelocity();
    }
    
    public: void setY(double y) {
        this->y = y;
        updateVelocity();
    }
    
    public: double getX() {
        return this->x;
    }
    
    public: double getY() {
        return this->y;
    }
};