//
//  Lighting.cpp
//  TheProject
//
//  Created by Ali Sultan on 5/6/15.
//  Copyright (c) 2015 Badr AlKhamissi. All rights reserved.
//

#include "Lighting.h"


Lightsource::Lightsource():detector(40,40)
{
    
}

Lightsource::Lightsource(sf::Sprite* base,sf::Sprite* object,int row,int col,int radius,double intensity):detector(40,40)
{
    this->intensity=intensity;
    startX=0;startY=0;
    this->row=row;
    this->col=col;
    this->radius=radius;
    this->base=base;
    this->object=object;
    flicker.restart();
    logicBoard=new bool[row*col];
    omega=(int)(omega*1000);
    omega/=1000;
}

Lightsource::Lightsource(sf::Sprite* base,sf::Sprite* object,int row,int col):detector(40,40) //dummy light object to reset lights and to determine light intensity for draw
{
    logicBoard=new bool; //dummy to prevent crash on destructor call
    this->base=base;
    this->object=object;
    this->row=row;
    this->col=col;
    flicker.restart();
}

void Lightsource::goggles()
{
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++){
            base[i*col+j].setColor(sf::Color(125,255,125));
            object[i*col+j].setColor(sf::Color(125,255,125));
        }
    
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
sf::Sprite* Lightsource::getBaseBoard()const
{
    return base;
}

sf::Sprite* Lightsource::getObjectBoard()const
{
    return object;
}

Lightsource::Lightsource(const Lightsource& copy):detector(40,40) //copy constructor for vector of sources
{
    detector=copy.detector;
    startX=copy.getCol();
    startY=copy.getStartY();
    radius=copy.getRadius();
    row=copy.getRow();
    col=copy.getCol();
    base=copy.getBaseBoard();
    object=copy.getObjectBoard();
    logicBoard=copy.getLogicBoard();
}

void Lightsource::illuminate(int x,int y) //calls recursive function with proper parameters (this is called in main)
{
    prepLogicBoard();
    startX=x;
    startY=y;
    if(x<col && y<row && x>=0 && y>=0)
        illuminate(startY,startX,STOP);
}

double Lightsource::getCurrentDistance(int i, int j) //get distance from center of illumination
{
    return sqrt((i-startY)*(i-startY)+(j-startX)*(j-startX));
}

double Lightsource::calculateLight(int i,int j) //calculates light level at location
{
    double lightResult;
    double distance=getCurrentDistance(i, j);
    
    lightResult=255*pow(intensity+0.01*sin(omega*flicker.getElapsedTime().asMilliseconds()), -1*distance);
    
    if(flicker.getElapsedTime().asMilliseconds()>=periodicTime) flicker.restart();
    this->lightResult=lightResult;
    
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
    
    if((i-1>=0) && getCurrentDistance(i-1,j)<=radius && !logicBoard[(i-1)*col+j])
        return UP;
    else if((j+1<col) && getCurrentDistance(i, j+1)<=radius && !logicBoard[i*col+(j+1)])
        return RIGHT;
    else if((i+1<row) && getCurrentDistance(i+1,j)<=radius && !logicBoard[(i+1)*col+j])
        return DOWN;
    else if((j-1>=0) && getCurrentDistance(i, j-1)<=radius && !logicBoard[i*col+(j-1)])
        return LEFT;
    
    else return STOP;
}

void Lightsource::illuminate(int i,int j,direction x)
{
    move(i, j, x);
    logicBoard[i*col+j]=true;
    
    if(calculateLight(i, j)>base[i*col+j].getColor().r){
        object[i*col+j].setColor(sf::Color(lightResult,lightResult,lightResult));
        base[i*col+j].setColor(sf::Color(lightResult,lightResult,lightResult));
    }
    
    x=getDirection(i, j);
    
    while(x!=STOP)
    {
        illuminate(i,j,x);
        x=getDirection(i, j);
    }
}

void Lightsource::directLight(int i,int j)
{
    double theta=atan2((float)(startY-i),(float)(startX-i));
    theta=theta*10;
    theta=(int)theta;
    theta/=10;
    double inc;
    if((i-startY)==0) inc=0;
    else if((j-startX)==0) inc=1;
    else inc=tan(theta);
    int iCrsr=i;
    int jCrsr=j;
    if(jCrsr>startX)
        while(getCurrentDistance(iCrsr, jCrsr)<=radius && checkBoundries(i, j))
        {
            logicBoard[iCrsr*col+jCrsr]=true;
            base[i*col+j].setColor(sf::Color::Black);
            object[i*col+j].setColor(sf::Color::Black);
            iCrsr=(int)(iCrsr+inc);
            jCrsr++;
        }
    else
        while(getCurrentDistance(iCrsr, jCrsr)<=radius && checkBoundries(i, j))
        {
            logicBoard[iCrsr*col+jCrsr]=true;
            base[i*col+j].setColor(sf::Color::Black);
            object[i*col+j].setColor(sf::Color::Black);
            iCrsr=(int)(iCrsr+inc);
            jCrsr--;
        }
}

bool Lightsource::checkBoundries(int i, int j)
{
    return (i<row && i>=0 && j<col && j>=0);
}


bool Lightsource::isObject(int i,int j)
{
    return detector.hasCollided(j, i);
}

void Lightsource::refreshLights()
{
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++){
            base[i*col+j].setColor(sf::Color(0,0,0));
            object[i*col+j].setColor(sf::Color(0,0,0));
        }
}

void Lightsource::prepLogicBoard()
{
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
            logicBoard[i*col+j]=false;
}


