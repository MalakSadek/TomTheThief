//
//  Player.h
//  TheProject
//
//  Created by Badr AlKhamissi on 4/29/15.
//  Copyright (c) 2015 Badr AlKhamissi. All rights reserved.
//

#ifndef __Game__Player__
#define __Game__Player__

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "Character.h"
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
    void move(int);
    void stand();
    void run();
private:
    textureHandler playerTexure;
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void animate(int, int);
    float speed = 10;
    int pAngle = 0;
    const int sizeX = 90*0.8, sizeY = 90*0.8;
    Sprite* pSprite = new Sprite;
    int facing=3;
};

#endif /* defined(__TheProject__Player__) */
