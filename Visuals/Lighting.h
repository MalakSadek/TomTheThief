//
//  Lighting.h
//  TheProject
//
//  Created by Ali Sultan on 5/6/15.
//  Copyright (c) 2015 Badr AlKhamissi. All rights reserved.
//

#ifndef __Game__Lighting__
#define __Game__Lighting__

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <cmath>

class Lightsource
{
public:
    Lightsource(sf::Sprite*,int,int,int,double); //row col radius intensitylevel
    Lightsource(sf::Sprite*,int,int);
    ~Lightsource();
    Lightsource(const Lightsource&);
    void illuminate(int,int);
    void refreshLights(); //dummy object refreshes lights
    int getRow()const;
    int getCol()const;
    int getRadius()const;
    int getStartX()const;
    int getStartY()const;
    bool* getLogicBoard()const;
    sf::Sprite* getSpriteBoard()const;
    
private:
    enum direction
    {
        UP,DOWN,LEFT,RIGHT,STOP
    };
    
    void illuminate(int,int,direction);
    void prepLogicBoard();
    double calculateLight(int,int);
    double getCurrentDistance(int,int);
    direction getDirection(int,int);
    void move(int&,int&,direction);
    sf::Clock flicker;
    
    bool* logicBoard;
    sf::Sprite* spriteBoard;
    int startX,startY;
    int radius;
    int row,col;
    sf::Color lightLevel;
    double intensity;
};

#endif /* defined(__TheProject__Lighting__) */
