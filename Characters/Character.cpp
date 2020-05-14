//
//  Character.cpp
//  TheProject
//
//  Created by Badr AlKhamissi on 5/6/15.
//  Copyright (c) 2015 Badr AlKhamissi. All rights reserved.
//

#include "Character.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <iostream>


using namespace std;

bool Character::collision(int i){
    if (things[i]!=-1) {
        return true;
    }else{
        return false;
    }
}

int Character::getTileNumber(int x,int y, int size){
    int posX = (x+size)/32;
    int posY = y/32;
    return posX+posY*79;
}

int Character::getTileNumber2(int x,int y, int size){
    int posX = (x+size)/32;
    int posY = y/32;
    return posX+posY*39;
}


void Character::setThingsPos(vector<int>& pos){
    things = pos;
}