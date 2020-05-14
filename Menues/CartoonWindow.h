//
//  CartoonWindow.h
//  Game frame
//
//  Created by Malak Sadek on 5/5/15.
//  Copyright (c) 2015 Malak Sadek. All rights reserved.
//

#ifndef __Game__CartoonWindow__
#define __Game__CartoonWindow__

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ResourcePath.hpp"
#include <vector>
#include <iostream>
#include "MainMenu.h"


using namespace sf;
using namespace std;

class Cartoon
{
private:
    
    RenderWindow* window;
    Sprite backgroundPicture;
    Texture backgroundTexture;

public:
    
    Cartoon(RenderWindow* window);
    void initializeScene();
    void eventHandling(MainMenu&);
    void drawScene();
    void gameloop(MainMenu&);
    
};

#endif /* defined(__Game_frame__CartoonWindow__) */
