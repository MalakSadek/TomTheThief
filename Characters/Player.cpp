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

Player::Player():playerTexure("Player"),detector(40,40){
    speed = 0.1;
    pSprite->setPosition(500, 500);
    pSprite->setTexture(*playerTexure.getTexture(facing*5));
    pSprite->setScale(0.5, 0.5);
    pSprite->setOrigin(45*0.5, 45*0.5);
}

Player::Player(int x, int y):playerTexure("Player"),detector(40,40){
    speed = 0.1;
    pSprite->setPosition(x, y);
    pSprite->setTexture(*playerTexure.getTexture(facing*5));
    pSprite->setScale(0.8, 0.8);
    pSprite->setOrigin(45*0.5, 45*0.5);
    iIndex=y/32;
    jIndex=x/32;
}


void Player::animate(int i, int j)const{
    pSprite->setTexture(*playerTexure.getTexture(j*5+i));
}

Sprite* Player::getPlayer(){
    return pSprite;
}

void Player::move(int dir, int level){
    
    if(speed<=9) speed+=acceleration;
    
    if (pAngle>=4) {
        pAngle = 0;
    }else{
        pAngle++;
    }
    
    if (level == 1 ) {
        int pos = 0;
        
        float x;
        float y;
        switch (dir) {
            case 1:
                x = getX();
                y = getY();
                pos = getTileNumber(x-32, y,0);
                j = 0;
                if (!(collision(pos))){
                    moveLeft();
                }
                break;
            case 2:
                x = getX();
                y = getY();
                pos = getTileNumber(x+32, y,0);
                j = 1;
                if (!(collision(pos))) {
                    moveRight();
                }
                break;
            case 3:
                x = getX();
                y = getY();
                pos = getTileNumber(x,y-32,0);
                j = 2;
                if (!(collision(pos))) {
                    moveUp();
                }
                break;
            case 4:
                x = getX();
                y = getY();
                pos = getTileNumber(x, y+32,0);
                j = 3;
                if (!(collision(pos))) {
                    moveDown();
                }
                break;
            default:
                break;
        }
        animate(pAngle, j);
    }else{
        jIndex=getX()/32;
        iIndex=(getY()+30*0.5)/32;
        switch (dir) {
            case 1:
                animate(pAngle, 0);
                if (!detector.hasCollided(iIndex, jIndex-1)){
                    moveLeft();
                }
                break;
            case 2:
                animate(pAngle, 1);
                if (!detector.hasCollided(iIndex,jIndex+1)) {
                    moveRight();
                }
                break;
            case 3:
                animate(pAngle, 2);
                if (!detector.hasCollided(iIndex-1,jIndex)) {
                    moveUp();
                }
                break;
            case 4:
                animate(pAngle, 3);
                if (!detector.hasCollided(iIndex+1,jIndex)) {
                    moveDown();
                }
                break;
            default:
                break;
        }
    }
}

bool Player::setMagnet(bool flag){
    attract = flag;
}

bool Player::getMagnet()const{
    return attract;
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

void Player::setPos(Vector2f pos){
    pSprite->setPosition(pos);
}


