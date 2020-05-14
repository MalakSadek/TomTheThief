//
//  GlowingBall.h
//  TheProject
//
//  Created by Badr AlKhamissi on 5/7/15.
//  Copyright (c) 2015 Badr AlKhamissi. All rights reserved.
//


#ifndef __Game__GlowingBall_h
#define __Game__GlowingBall_h

#include "TextureHandler.h"
#include "Player.h"
#include "math.h"


class levelPickUp{
public:
    levelPickUp(int x, int y, int _cX, int _cY):gbTxr("GlowingBall"){
        cX = _cX;
        cY = _cY;
        gbSprite->setPosition(x, y);
        gbSprite->setTexture(*gbTxr.getTexture(cX*11+cY));
        gbSprite->setScale(4,4);
        clock.restart();
    }
    
    void animate(){
        sec = clock.getElapsedTime();
        if (sec.asSeconds()>0.2) {
            if(j == 4){
                j = 0;
            }
            if (i == 5) {
                i = 0;
                j++;
            }else{
                i++;
            }
            clock.restart();
        }
        gbSprite->setTexture(*gbTxr.getTexture((j)+(i)*11));
    }
    
    bool collect(Player& p){
        float pX = p.getX();
        float pY = p.getY();
        float disX = gbSprite->getPosition().x + 32*2 - pX;
        float disY = gbSprite->getPosition().y + 32*2 - pY;
        if (sqrt(pow(disX, 2) + pow(disY, 2)) < 32*2)
        {
            return true;
        }else{
            return false;
        }
    }
    
    Sprite* getSprite(){
        return gbSprite;
    }
    
    int getX()const{
        return gbSprite->getPosition().x;
    }
    
    int getY()const{
        return gbSprite->getPosition().y;
    }
private:
    textureHandler gbTxr;
    const int size = 32;
    Sprite* gbSprite = new Sprite;
    int i = 0, j = 0;
    int cX, cY;
    Clock clock;
    Time sec;
};
#endif
