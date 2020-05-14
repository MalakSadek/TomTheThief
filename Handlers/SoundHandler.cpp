//
//  SoundHandler.cpp
//  TheProject
//
//  Created by Ali Sultan on 5/2/15.
//  Copyright (c) 2015 Badr AlKhamissi. All rights reserved.
//

#include <SFML/Audio.hpp>
#include "SoundHandler.h"
#include "ResourcePath.hpp"
#include <stdio.h>

soundHandler::soundHandler(std::string type)
{
    this->type = type;
    effect = NULL;
    if(type=="coinPickup")
    {
        
        if (!buffer.loadFromFile(resourcePath() + "coin_pickup.aiff"))
            return EXIT_FAILURE;
        effect = new sf::Sound;
        effect->setBuffer(buffer);
        effect->setVolume(30);
    }
    if(type=="key")
    {
        if (!buffer.loadFromFile(resourcePath() + "key_pickup.wav"))
            return EXIT_FAILURE;
        effect = new sf::Sound;
        effect->setBuffer(buffer);
        effect->setVolume(30);
    }
    if(type=="footSteps")
    {
        if (!buffer.loadFromFile(resourcePath() + "FootStep.wav"))
            return EXIT_FAILURE;
        effect = new sf::Sound;
        effect->setBuffer(buffer);
        effect->setVolume(10);
    }
    if(type=="Greed")
    {
        if(!music.openFromFile(resourcePath()+"Greed.wav"))
            return EXIT_FAILURE;
    }
    if(type=="Apocalypse")
    {
        if(!music.openFromFile(resourcePath()+"Apocalypse.wav"))
            return EXIT_FAILURE;
    }
    if(type=="Sacrificial")
    {
        if(!music.openFromFile(resourcePath()+"Sacrificial.wav"))
            return EXIT_FAILURE;
    }
    music.setVolume(30);
}

soundHandler::soundHandler(const soundHandler& rhs)
{
    type = rhs.type;
    effect = NULL;
    if(type=="coinPickup")
    {
        if (!buffer.loadFromFile(resourcePath() + "coin_pickup.aiff"))
            return EXIT_FAILURE;
        effect = new sf::Sound;
        effect->setBuffer(buffer);
        effect->setVolume(30);
    }
    if(type=="key")
    {
        if (!buffer.loadFromFile(resourcePath() + "key_pickup.wav"))
            return EXIT_FAILURE;
        effect = new sf::Sound;
        effect->setBuffer(buffer);
        effect->setVolume(30);
    }
    if(type=="footSteps")
    {
        if (!buffer.loadFromFile(resourcePath() + "FootStep.wav"))
            return EXIT_FAILURE;
        effect = new sf::Sound;
        effect->setBuffer(buffer);
        effect->setVolume(10);
    }
}


sf::Sound* soundHandler::getSound()
{
    return effect;
}

soundHandler::~soundHandler()
{
    if(effect != NULL) delete effect;
}