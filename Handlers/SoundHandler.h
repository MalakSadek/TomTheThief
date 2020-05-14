//
//  SoundHandler.h
//  TheProject
//
//  Created by Ali Sultan on 5/2/15.
//  Copyright (c) 2015 Badr AlKhamissi. All rights reserved.
//

#ifndef __Game__SoundHandler__
#define __Game__SoundHandler__

#include <stdio.h>
#include <SFML/Audio.hpp>

class soundHandler
{
public:
    soundHandler(std::string);
    soundHandler(const soundHandler&);
    ~soundHandler();
    sf::Sound* getSound();
    void play()
    {
        music.play();
    }
    void pause()
    {
        music.pause();
    }
    void stop()
    {
        music.stop();
    }
    bool paused()
    {
        if(music.getStatus()==sf::Music::Status::Paused) return true;
    }
    
    
private:
    
    sf::Music music;
    std::string type;
    sf::SoundBuffer buffer;
    sf::Sound* effect;
};

#endif /* defined(__TheProject__SoundHandler__) */
