//
//  Lighting.cpp
//  TheProject
//
//  Created by Ali Sultan on 5/6/15.
//  Copyright (c) 2015 Badr AlKhamissi. All rights reserved.
//

#include "Lighting.h"


Lightsource::Lightsource(sf::Sprite* spriteBoard,int row,int col,int radius,double intensity)
{
    this->intensity=intensity;
    startX=0;startY=0;
    this->row=row;
    this->col=col;
    this->radius=radius;
    this->spriteBoard=spriteBoard;
    logicBoard=new bool[row*col];
}

Lightsource::Lightsource(sf::Sprite* board,int row,int col) //dummy light object to reset lights and to determine light intensity for draw
{
    logicBoard=new bool; //dummy to prevent crash on destructor call
    spriteBoard=board;
    this->row=row;
    this->col=col;
}

int Lightsource::getRow()const //getters
{
    return row;
}
int Lightsource::getCol()const
{
    return col;
}
int Lightsource::getRadius()const
{
    return radius;
}
int Lightsource::getStartX()const
{
    return startX;
}
int Lightsource::getStartY()const
{
    return startY;
}
bool* Lightsource::getLogicBoard()const
{
    return logicBoard;
}
sf::Sprite* Lightsource::getSpriteBoard()const
{
    return spriteBoard;
}

Lightsource::Lightsource(const Lightsource& copy) //copy constructor for vector of sources
{
    startX=copy.getCol();
    startY=copy.getStartY();
    radius=copy.getRadius();
    row=copy.getRow();
    col=copy.getCol();
    spriteBoard=copy.getSpriteBoard();
    logicBoard=copy.getLogicBoard();
}

void Lightsource::illuminate(int x,int y) //calls recursive function with proper parameters (this is called in main)
{
    prepLogicBoard();
    startX=(x+1<col)?x+1:x;
    startY=(y+1<row)?y+1:y;
    illuminate(startY,startX,STOP);
}

double Lightsource::getCurrentDistance(int i, int j) //get distance from center of illumination
{
    return sqrt((i-startY)*(i-startY)+(j-startX)*(j-startX));
}

double Lightsource::calculateLight(int i,int j) //calculates light level at location
{
    double lightResult;
    if(flicker.getElapsedTime().asMilliseconds()<100){
        lightResult=255*pow(1./(intensity-0.01), getCurrentDistance(i, j));
        lightLevel=sf::Color(lightResult,lightResult,lightResult);
    }
    else if(flicker.getElapsedTime().asMilliseconds()<200){
        lightResult=255*pow(1./(intensity), getCurrentDistance(i, j));
        lightLevel=sf::Color(lightResult,lightResult,lightResult);
    }
    else if(flicker.getElapsedTime().asMilliseconds()<=300)
    {
        lightResult=255*pow(1./(intensity+0.01), getCurrentDistance(i, j));
        lightLevel=sf::Color(lightResult,lightResult,lightResult);
        flicker.restart();
    }
    return lightResult; //return independent double to avoid calculating light level twice
}

void Lightsource::move(int& i,int& j,direction x)
{
    switch(x)
    {
        case UP: i--; break;
        case DOWN: i++; break;
        case LEFT: j--; break;
        case RIGHT: j++; break;
        case STOP:;
    }
}

Lightsource::direction Lightsource::getDirection(int i,int j)
{
    
    if((i-1>=0) && getCurrentDistance(i-1,j)<radius && !logicBoard[(i-1)*col+j])
        return UP;
    else if((j+1<col) && getCurrentDistance(i, j+1)<radius && !logicBoard[i*col+(j+1)])
        return RIGHT;
    else if((i+1<row) && getCurrentDistance(i+1,j)<radius && !logicBoard[(i+1)*col+j])
        return DOWN;
    else if((j-1>=0) && getCurrentDistance(i, j-1)<radius && !logicBoard[i*col+(j-1)])
        return LEFT;
    
    else return STOP;
}

void Lightsource::illuminate(int i,int j,direction x)
{
    move(i, j, x);
    
    logicBoard[i*col+j]=true;
    
    if(calculateLight(i, j)>spriteBoard[i*col+j].getColor().r)
        spriteBoard[i*col+j].setColor(lightLevel);
    
    x=getDirection(i, j);
    
    while(x!=STOP)
    {
        illuminate(i,j,x);
        x=getDirection(i, j);
    }
}

void Lightsource::refreshLights()
{
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
            spriteBoard[i*col+j].setColor(sf::Color(0,0,0));
}

void Lightsource::prepLogicBoard()
{
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
            logicBoard[i*col+j]=false;
}

Lightsource::~Lightsource()
{
    delete logicBoard;
}
