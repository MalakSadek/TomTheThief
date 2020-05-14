//
//  LevelObject.h
//  Game
//
//  Created by Ali Sultan on 5/9/15.
//  Copyright (c) 2015 Ali Sultan. All rights reserved.
//

#ifndef __Game__LevelObject__
#define __Game__LevelObject__

#include <stdio.h>
#include "GlowingBall.h"
#include "Coins.h"
#include "Enemy.h"
#include <iostream>

template <class T> class Object {
public:
    Object()
    {
        thing = new T[1];
    };
    Object(int x)
    {
        thing = new T[x];
        size=x;
    };
    ~Object()
    {
        if(thing!=NULL) delete[] thing;
    };
    void setSize(int x)
    {
        if(thing!=NULL) delete[] thing;
        thing = new T[x];
        size=x;
    }
    int getSize()
    {
        return size;
    };
    void reset()
    {
        delete[] thing;
    };
    T at(int x)
    {
        if(x>=0 && x<size){
            return *thing+x;
        }
        else
        {
            std::cerr<<"BAD ACCESS\n";
        }
    }
private:
    T* thing;
    int size;
};


#endif /* defined(__Game__LevelObject__) */
