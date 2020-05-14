//
//  TextureHandler.cpp
//  TheProject
//  Created by Ali Sultan on 5/2/15.
//  Copyright (c) 2015 Badr AlKhamissi. All rights reserved.


#include "TextureHandler.h"
#include "ResourcePath.hpp"

textureHandler::textureHandler(std::string type)
{
    this->type = type;
    if(type=="Wall"){
        Size=1;
        wtxr = new sf::Texture;
        if(!wtxr->loadFromFile(resourcePath()+"wall.jpg",sf::IntRect(0,0,32,32)))
            return EXIT_FAILURE;
        wtxr->setSmooth(true);
    }
    if(type=="Wall2"){
        Size=223;
        w2txr = new sf::Texture[Size];
        for(int i=0;i<16;i++)
            for(int j=0;j<14;j++)
                if(!w2txr[i*14+j].loadFromFile(resourcePath()+"level1Txr.png",sf::IntRect(32*j,32*i,32,32)))
                    return EXIT_FAILURE;
        w2txr->setSmooth(true);
    }
    else if(type=="Door")
    {
        Size = 4;
        dtxr = new sf::Texture[4];
        for(int i=0;i<4;i++)
        {
            if(!(dtxr+i)->loadFromFile(resourcePath()+"door2.png",sf::IntRect(0,i*32,64,32)))
               return EXIT_FAILURE;
        }
    }
    else if(type=="Key")
    {
        Size = 1;
        ktxr = new sf::Texture;
        if(!ktxr->loadFromFile(resourcePath()+"key.png",sf::IntRect(0,0,30,22)))
            return EXIT_FAILURE;
    }
    else if(type=="Terrain_WoodenFloor"){
        Size=64;
        ttxr = new sf::Texture[64];
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                if(!ttxr[i*8+j].loadFromFile(resourcePath()+"WoodenFloor.png",sf::IntRect(32*j,32*i,32,32)))
                    return EXIT_FAILURE;
    }
    
    else if(type=="Terrain_Mountain")
    {
        ttxr=new sf::Texture[225];
        Size =225;
        for(int i=0;i<15;i++)
        {
            for(int j=0;j<15;j++)
            {
                if(!ttxr[i*15+j].loadFromFile(resourcePath()+"mountain_landscape.png",sf::IntRect(j*32,i*32,32,32)))
                    return EXIT_FAILURE;
            }
        }
    }
    else if(type=="Player")
    {
        ptxr = new sf::Texture[20];
        Size=20;
        for(int i=0;i<4;i++)
            for(int j=0;j<5;j++){
                if(!(ptxr+j+i*5)->loadFromFile(resourcePath()+"link.png",sf::IntRect(90*j,90*i,90,90)))
                    return EXIT_FAILURE;
            }
        
    }
    else if(type=="Enemy")
    {
        etxr=new sf::Texture[16];
        Size=16;
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                if(!etxr[i*4+j].loadFromFile(resourcePath()+"hokot3a.png",sf::IntRect(80*i,80*j,80,80)))
                    return EXIT_FAILURE;
            }
        }
    }
    
    else if(type=="GlowingBall")
    {
        otxr = new sf::Texture[12*8];
        Size=12*8;
        for(int i=0;i<8;i++)
            for(int j=0;j<12;j++){
                if(!(otxr+j+i*12)->loadFromFile(resourcePath()+"glowing_balls.png",sf::IntRect(32*j,32*i,32,32)))
                    return EXIT_FAILURE;
                (otxr+j+i*12)->setSmooth(true);
            }
    }
    else if(type=="Coin"){
        otxr = new sf::Texture[6];
        Size=6;
        for (int i=0; i<6; i++)
        {
            if(!(otxr+i)->loadFromFile(resourcePath() + "coins.png", sf::IntRect(66*i, 0, 66, 66))){
                return EXIT_FAILURE;
            }
            (otxr+i)->setSmooth(true);
        }
    }
}

textureHandler::textureHandler(const textureHandler& rhs){
    this->type = type;
    if(type=="Wall"){
        Size=1;
        wtxr = new sf::Texture;
        if(!wtxr->loadFromFile(resourcePath()+"wall.jpg",sf::IntRect(0,0,32,32)))
            return EXIT_FAILURE;
    }
    if(type=="Wall2"){
        Size=223;
        w2txr = new sf::Texture[Size];
        for(int i=0;i<16;i++)
            for(int j=0;j<14;j++)
                if(!w2txr[i*14+j].loadFromFile(resourcePath()+"level1Txr.png",sf::IntRect(32*j,32*i,32,32)))
                    return EXIT_FAILURE;
        w2txr->setSmooth(true);
    }
    else if(type=="Door")
    {
        Size = 4;
        dtxr = new sf::Texture[4];
        for(int i=0;i<4;i++)
        {
            if(!(dtxr+i)->loadFromFile(resourcePath()+"door2.png",sf::IntRect(0,i*32,32,32)))
                return EXIT_FAILURE;
        }
    }
    else if(type=="Key")
    {
        Size = 1;
        ktxr = new sf::Texture;
        if(!ktxr->loadFromFile(resourcePath()+"key.png",sf::IntRect(0,0,30,22)))
            return EXIT_FAILURE;
    }
    else if(type=="Terrain_WoodenFloor"){
        Size=64;
        ttxr = new sf::Texture[64];
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++)
                if(!ttxr[i*8+j].loadFromFile(resourcePath()+"WoodenFloor.png",sf::IntRect(32*j,32*i,32,32)))
                    return EXIT_FAILURE;
    }
    
    else if(type=="Terrain_Mountain")
    {
        ttxr=new sf::Texture[225];
        Size =225;
        for(int i=0;i<15;i++)
        {
            for(int j=0;j<15;j++)
            {
                if(!ttxr[i*15+j].loadFromFile(resourcePath()+"mountain_landscape.png",sf::IntRect(j*32,i*32,32,32)))
                    return EXIT_FAILURE;
            }
        }
    }
    else if(type=="Player")
    {
        ptxr = new sf::Texture[20];
        Size=20;
        for(int i=0;i<4;i++)
            for(int j=0;j<5;j++){
                if(!(ptxr+j+i*5)->loadFromFile(resourcePath()+"link.png",sf::IntRect(90*j,90*i,90,90)))
                    return EXIT_FAILURE;
                (ptxr+j+i*5)->setSmooth(true);
            }
        
    }
    else if(type=="Enemy")
    {
        etxr=new sf::Texture[16];
        Size=16;
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                if(!etxr[i*4+j].loadFromFile(resourcePath()+"hokot3a.png",sf::IntRect(80*i,80*j,80,80)))
                    return EXIT_FAILURE;
            }
        }
    }
    
    else if(type=="GlowingBall")
    {
        otxr = new sf::Texture[12*8];
        Size=12*8;
        for(int i=0;i<8;i++)
            for(int j=0;j<12;j++){
                if(!(otxr+j+i*12)->loadFromFile(resourcePath()+"glowing_balls.png",sf::IntRect(32*j,32*i,32,32)))
                    return EXIT_FAILURE;
                (otxr+j+i*12)->setSmooth(true);
            }
    }
    else if(type=="Coin"){
        otxr = new sf::Texture[6];
        Size=6;
        for (int i=0; i<6; i++)
        {
            if(!(otxr+i)->loadFromFile(resourcePath() + "coins.png", sf::IntRect(66*i, 0, 66, 66))){
                return EXIT_FAILURE;
            }
            (otxr+i)->setSmooth(true);
        }
    }
}

textureHandler::~textureHandler()
{
    if(type=="Terrain_WoodenFloor") delete [] ttxr;
    else if(type=="Terrain_Wall") delete[] ttxr;
    //else if(type=="Wall2") delete[] w2txr;
    else if(type=="Coin" || type=="GlowingBall") delete [] otxr;
    else if(type=="Player") delete [] ptxr;
    else if(type=="Enemy") delete[] etxr;
    else if(type=="Wall") delete wtxr;
    else if(type=="Door") delete[] dtxr;
    else if(type=="Key") delete ktxr;
}


sf::Texture* textureHandler::getTexture(int index)const
{
    if(type=="Player") return getPlayer(index);
    else if(type=="Coin" || type=="GlowingBall") return getObject(index);
    else if(type=="Enemy") return getEnemy(index);
    else if(type=="Wall") return wtxr;
    else if(type=="Terrain_WoodenFloor"|| type=="Terrain_Mountain")
        return getTerrain(index);
    else if(type=="Key")return getKey(0);
    else if(type=="Wall2")return getWall2(index);
    else if(type=="Door")return getDoor(index);
}

std::string textureHandler::getType() const
{
    return type;
}

int textureHandler::size()
{
    return Size;
}

sf::Texture* textureHandler::getEnemy(int index)const
{
    if(index<Size && index>=0) return etxr+index;
    else std::cout<<"INVALIDE TEXTURE INDEX SPECIFIED\n";
}

sf::Texture* textureHandler::getDoor(int index)const
{
    if(index<Size && index>=0) return dtxr+index;
    else std::cout<<"INVALID TEXTURE INDEX SPECIFIED\n";
}

sf::Texture* textureHandler::getTerrain(int index) const
{
    if(index<Size && index>=0)return ttxr+index;
    else std::cout<<"INVALID TEXTURE INDEX SPECIFIED\n";
}

sf::Texture* textureHandler::getObject(int index) const
{
    if(index<Size && index>=0)return otxr+index;
    else std::cout<<"INVALID TEXTURE INDEX SPECIFIED\n";
}

sf::Texture* textureHandler::getPlayer(int index)const
{
    if(index<Size && index>=0)return ptxr+index;
    else std::cout<<"INVALID TEXTURE INDEX SPECIFIED\n";
}

sf::Texture* textureHandler::getWall2(int index)const
{
    if(index<Size && index>=0)return w2txr+index;
    else std::cout<<"INVALID TEXTURE INDEX SPECIFIED\n";
}

sf::Texture* textureHandler::getKey(int index)const
{
    if(index<Size && index>=0)return ktxr+index;
    else std::cout<<"INVALID TEXTURE INDEX SPECIFIED\n";
}