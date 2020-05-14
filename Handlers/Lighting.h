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
#include "CollisionHandler.h"
#define periodicTime 2000

class Lightsource
{
public:
    Lightsource();
    Lightsource(sf::Sprite*,sf::Sprite*,int,int,int,double); //row col radius intensitylevel
    Lightsource(sf::Sprite*,sf::Sprite*,int,int);
    //    ~Lightsource();
    Lightsource(const Lightsource&);
    void illuminate(int,int);
    void setParameters(sf::Sprite*,sf::Sprite*,int,int,int,int);
    void refreshLights(); //dummy object refreshes lights
    void goggles();
    int getRow()const;
    int getCol()const;
    int getRadius()const;
    int getStartX()const;
    int getStartY()const;
    bool* getLogicBoard()const;
    sf::Sprite* getBaseBoard()const;
    sf::Sprite* getObjectBoard()const;
    void directLight(int,int);
    bool isObject(int,int);
    CollisionDetector detector;
    bool checkBoundries(int,int);
    sf::Clock flicker; //ADDED 10:03
    bool goggleActive;
    
    void setParam(sf::Sprite* base,sf::Sprite* object,int row,int col,int radius,double intensity)
    {
        this->intensity=intensity;
        startX=0;startY=0;
        this->row=row;
        this->col=col;
        this->radius=radius;
        this->base=base;
        this->object=object;
        logicBoard=new bool[row*col];
        omega=(int)(omega*1000);
        omega/=1000;
    }
    
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
    double omega=2*3.14*(1./periodicTime);
    bool* logicBoard;
    sf::Sprite* base;
    sf::Sprite* object;
    int startX,startY;
    int radius;
    int row,col;
    double lightResult;
    double intensity;
};

#endif /* defined(__TheProject__Lighting__) */
