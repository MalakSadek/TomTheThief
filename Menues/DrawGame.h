//
//  DrawGame.h
//  Game frame
//
//  Created by Malak Sadek on 5/5/15.
//  Copyright (c) 2015 Malak Sadek. All rights reserved.
//

#ifndef __Game__DrawGame__
#define __Game__DrawGame__

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ResourcePath.hpp"
#include <vector>
#include <iostream>

using namespace sf;
using namespace std;

class Game
{
private:
    
    RenderWindow* window;
    Sprite backgroundPicture;
    Texture backgroundTexture;

public:
    Game(RenderWindow* window);
    void initializeScene();
    void eventHandling();
    void drawScene();
    void gameLoop();
};

#endif /* defined(__Game_frame__DrawGame__) */
