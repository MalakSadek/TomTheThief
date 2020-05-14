//
//  CollisionHandler.h
//  Game
//
//  Created by Ali Sultan on 5/9/15.
//  Copyright (c) 2015 Ali Sultan. All rights reserved.
//

#ifndef __Game__CollisionHandler__
#define __Game__CollisionHandler__

#include <stdio.h>
#include <iostream>

class CollisionDetector
{
public:
    
    CollisionDetector(int sizeX,int sizeY)
    {
        setCollisionMapSize(sizeX,sizeY);
    };
    
    void setCollisionMapSize(int sizeX,int sizeY)
    {
        this->sizeX=sizeX;
        this->sizeY=sizeY;
        size=sizeX*sizeY;
        objectLayer = new bool[size];
        for(int i=0;i<sizeY;i++)
            for(int j=0;j<sizeX;j++)
                objectLayer[i*sizeX+j]=0;
    };
    
    void setNonColliderObject(int index)
    {
        if(index>=0 && index<size)
            objectLayer[index]=0;
        else
            std::cerr<<"BAD ACCESS\n";
    }
  
    void setColliderObject(int index)
    {
        if(index>=0 && index<size)
            objectLayer[index]=1;
        else
            std::cerr<<"BAD ACCESS\n";
    };
    bool hasCollided(int x,int y)
    {
        if(x<sizeX && y<sizeY)
            return objectLayer[x*sizeX+y];
        else
            return true;
    };
    
    void reset()
    {
        for(int i=0;i<sizeY;i++)
            for(int j=0;j<sizeX;j++)
                objectLayer[i*sizeX+j]=0;
    }
    
    int getSize()const
    {
        return size;
    };
    
    int getSizeX()const
    {
        return sizeX;
    };
    
    int getSizeY()const
    {
        return sizeY;
    };
    
    bool* getObjectLayer()const
    {
        return objectLayer;
    };
    
    CollisionDetector(const CollisionDetector& rhs)
    {
        objectLayer = new bool [rhs.getSize()];
        for(int i=0;i<rhs.getSizeY();i++)
            for(int j=0;j<rhs.getSizeX();j++)
                objectLayer[i*sizeY+j]=*(rhs.getObjectLayer()+i*getSizeY()+j);
    };
    
    CollisionDetector& operator=(const CollisionDetector& rhs)
    {
        for(int i=0;i<rhs.getSizeY();i++)
            for(int j=0;j<rhs.getSizeX();j++)
                objectLayer[i*sizeY+j]=*(rhs.getObjectLayer()+i*getSizeY()+j);
        return *this;
    };

private:
    bool* objectLayer;
    int size,sizeX,sizeY;
};

#endif /* defined(__Game__CollisionHandler__) */
