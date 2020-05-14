//
//  Player.h
//  TheProject
//
//  Created by Badr AlKhamissi on 4/29/15.
//  Copyright (c) 2015 Badr AlKhamissi. All rights reserved.
//

#ifndef __TheProject__Player__
#define __TheProject__Player__

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "Character.h"
#include "CollisionHandler.h"
#include "TextureHandler.h"
using namespace sf;
using namespace std;

class Player: public Character{
public:
    Player();
    Player(int,int);
    Sprite* getPlayer();
    int getX()const;
    int getY()const;
    void move(int,int);
    bool setMagnet(bool);
    bool getMagnet()const;
    void stand();
    void run();
    void setPos(Vector2f);
    CollisionDetector detector;
    int jIndex;
    int iIndex;
    void resetSpeed(){speed=0;}
private:
    textureHandler playerTexure;
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void animate(int, int)const;
    float acceleration=0.09;
    float speed = 0;
    float pAngle = 0;
    const int sizeX = 90*0.8, sizeY = 90*0.8;
    Sprite* pSprite = new Sprite;
    int facing=3;
    bool attract = false;
    int j;
};

#endif /* defined(__TheProject__Player__) */
