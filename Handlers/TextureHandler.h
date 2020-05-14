//
//  TextureHandler.h
//  TheProject
//
//  Created by Ali Sultan on 5/2/15.
//  Copyright (c) 2015 Badr AlKhamissi. All rights reserved.
//

#ifndef __Game__TextureHandler__
#define __Game__TextureHandler__

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class textureHandler
{
    
public:
    textureHandler(std::string);
    textureHandler(const textureHandler& rhs);
    ~textureHandler();
    sf::Texture* getTerrain(int)const;
    sf::Texture* getObject(int)const;
    sf::Texture* getPlayer(int)const;
    sf::Texture* getTexture(int)const;
    sf::Texture* getEnemy(int)const;
    sf::Texture* getKey(int)const;
    sf::Texture* getDoor(int)const;
    sf::Texture* getWall2(int)const;
    std::string getType()const;
    
    int size();
private:
    int Size;
    sf::Texture* dtxr=NULL; //door texture
    sf::Texture* ktxr=NULL; //keyTexture
    sf::Texture* etxr=NULL; //enemy Texture
    sf::Texture* ttxr=NULL; //Terrain texture
    sf::Texture* otxr=NULL;  //Object texture
    sf::Texture* ptxr=NULL;  //player texture
    sf::Texture* wtxr=NULL;  //wall texture
    sf::Texture* w2txr=NULL;  //level 1 wall texture
    std::string type;
};



#endif /* defined(__TheProject__TextureHandler__) */
