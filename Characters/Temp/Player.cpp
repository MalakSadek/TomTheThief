//
//  Player.cpp
//  TheProject
//
//  Created by Badr AlKhamissi on 4/29/15.
//  Copyright (c) 2015 Badr AlKhamissi. All rights reserved.
//

#include "Player.h"
#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <iostream>
#include "TextureHandler.h"

using namespace sf;
using namespace std;

Player::Player():playerTexure("Player")
{
    speed = 20;
    pSprite->setPosition(50, 50);
    pSprite->setTexture(*playerTexure.getTexture(facing*5));
    pSprite->setScale(0.8, 0.8);
}

Player::Player(int x, int y):playerTexure("Player"){
    speed = 20;
    pSprite->setPosition(x, y);
    pSprite->setTexture(*playerTexure.getTexture(facing*5));
    pSprite->setScale(0.8, 0.8);
}


void Player::animate(int i, int j){
    pSprite->setTexture(*playerTexure.getTexture(j*5+i));
}

Sprite* Player::getPlayer(){
    return pSprite;
}

void Player::move(int dir){
    
    if (pAngle>=4) {
        pAngle = 0;
    }else{
        pAngle++;
    }
    
    int pos = 0;
    
    float x;
    float y;

    switch (dir) {
        case 1:
            x = getX()+(90*0.8)/2;
            y = getY()+(90*0.8)-28;
            pos = getTileNumber(x-32, y,0);
            if (!(collision(pos))){
                moveLeft();
            }
            animate(pAngle, 0);
            break;
        case 2:
            x = getX()+(90*0.8)/2;
            y = getY()+(90*0.8)-28;
             pos = getTileNumber(x+32, y,0);
            if (!(collision(pos))) {
                moveRight();
            }
            animate(pAngle, 1);
            break;
        case 3:
            x = getX()+(90*0.8)/2;
            y = getY()+28;
            pos = getTileNumber(x,y-32,0);
            if (!(collision(pos))) {
                moveUp();
            }
            animate(pAngle, 2);
            break;
        case 4:
            x = getX()+(90*0.8)/2;
            y = getY();
            pos = getTileNumber(x, y+32,0);
            if (!(collision(pos))) {
                moveDown();
            }
            animate(pAngle, 3);
            break;
        default:
            break;
    }
}

void Player::stand()
{
    if(facing!=1)
        pSprite->setTexture(*playerTexure.getTexture(facing*5));
    else
        pSprite->setTexture(*playerTexure.getTexture(facing*5+4));
}

void Player::moveDown(){
    pSprite->move(0, speed);
}

void Player::moveUp(){
    pSprite->move(0, -speed);
}

void Player::moveRight(){
    pSprite->move(speed, 0);
}

void Player::moveLeft(){
    pSprite->move(-speed, 0);
}

int Player::getX()const{
    return pSprite->getPosition().x;
}

int Player::getY()const{
    return pSprite->getPosition().y;
}


