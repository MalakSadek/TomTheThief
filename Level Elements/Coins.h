//
//  Coins.h
//  TheProject
//
//  Created by Badr AlKhamissi on 4/29/15.
//  Copyright (c) 2015 Badr AlKhamissi. All rights reserved.
//

#ifndef __Game__Coins__
#define __Game__Coins__

#include <stdio.h>
#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "ResourcePath.hpp"
#include "SoundHandler.h"
#include "TextureHandler.h"
#include "Lighting.h"
#include <cmath>


using namespace sf;

class Coins{
    
public:
    
    Coins(int, int);
    void rotate();
    Sprite* getSprite();
    int getXPos()const;
    int getYPos()const;
    float getcAngle()const;
    bool getState()const;
    void setState(bool);
    bool collectCoin(Player&);
    Coins(const Coins&);
    void attractCoin(Player&);
    void dimCoin(Lightsource&,float,float); //ADDED WED 10:01
    
private:
    double omega;
    Sprite* cSprite;
    float cAngle;
    bool state;
    textureHandler coinTexture;
    soundHandler pickupCoin;
};

#endif /* defined(__TheProject__Coins__) */
