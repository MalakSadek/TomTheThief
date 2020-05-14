//
//  Coins.cpp
//  TheProject
//
//  Created by Badr AlKhamissi on 4/29/15.
//  Copyright (c) 2015 Badr AlKhamissi. All rights reserved.
//

#include "Coins.h"
#include <math.h>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "TextureHandler.h"
#include "SoundHandler.h"


using namespace sf;
using namespace std;

Coins::Coins(int xpos, int ypos) : coinTexture("Coin"), pickupCoin("coinPickup")
{
    cSprite=new Sprite;
    const float size = 66.5;
    cAngle=0;
    state=false;
    cSprite->setPosition(xpos,ypos);
    cSprite->setTexture(*coinTexture.getTexture(0));
    cSprite->setScale(0.5, 0.5);
    omega=2*3.14*(1./2000);
    omega=(int)(omega*1000);
    omega/=1000;
}

Coins::Coins(const Coins& rhs) : coinTexture("Coin"), pickupCoin("coinPickup")
{
    this->cSprite = new Sprite;
    this->cAngle=rhs.getcAngle();
    this->state=rhs.getState();
    this->cSprite->setPosition(rhs.getXPos(),rhs.getYPos());
    cSprite->setTexture(*coinTexture.getTexture(0));
    cSprite->setScale(0.75, 0.75);
    omega=2*3.14*(1./periodicTime);
    omega=(int)(omega*1000);
    omega/=1000;
}


void Coins::rotate(){
    cSprite->setTexture(*coinTexture.getTexture((int)cAngle));
    cAngle+=0.05;
    if(cAngle>5) cAngle=0;
}

Sprite* Coins::getSprite(){
    return cSprite;
}

bool Coins::collectCoin(Player& p){
    float pX = p.getX();
    float pY = p.getY();
    float disX = getXPos() - pX;
    float disY = getYPos() - pY;
    
    if (p.getMagnet()) {
        attractCoin(p);
    }
    
    if (sqrt(disX*disX + disY*disY )< 35 )
    {
        if(!state)
            pickupCoin.getSound()->play();
        return true;
    }else{
        return false;
    }
}

bool Coins::getState()const{
    return state;
}

void Coins::setState(bool s){
    state = s;
}

float Coins::getcAngle()const{
    return cAngle;
}

int Coins::getXPos()const{
    return cSprite->getPosition().x;
}

int Coins::getYPos()const{
    return cSprite->getPosition().y;
}

void Coins::dimCoin(Lightsource& light,float dist,float base)
{
    float lightIntensity;
    lightIntensity = 255*pow(base-0.1*sin(omega*light.flicker.getElapsedTime().asMilliseconds()+3.14/2),-1*dist);
    cSprite->setColor(Color(lightIntensity,lightIntensity,lightIntensity));
}

void Coins::attractCoin(Player& p){
    
    float pX = p.getX();
    float pY = p.getY();
    float disX = getXPos() - pX;
    float disY = getYPos() - pY;
    
    if (sqrt(disX*disX + disY*disY )< 200 ){
        if (getXPos()>p.getX()) {
            cSprite->move(-2,0);
        }else if(getXPos()<p.getX()){
            cSprite->move(2,0);
        }
        if (getYPos()>p.getY()) {
            cSprite->move(0,-2);
        }else{
            cSprite->move(0,2);
        }
    }
}


