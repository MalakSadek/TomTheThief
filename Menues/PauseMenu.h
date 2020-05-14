//
//  PauseMenu.h
//  Game frame
//
//  Created by Malak Sadek on 5/5/15.
//  Copyright (c) 2015 Malak Sadek. All rights reserved.
//

#ifndef __Game__PauseMenu__
#define __Game__PauseMenu__

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ResourcePath.hpp"
#include <vector>
#include <iostream>

using namespace sf;
using namespace std;

class PauseMenu
{
private:
    RenderWindow* window;
    
    int currentlySelectedIndex;
    
    Text titleText;
    Text coincount;
    vector<Text> menuItems;
    Font titleFont, menuItemFont;
        
    Sprite backgroundPicture;
    Texture backgroundTexture;
    
    Sprite coinPicture;
    Texture coinTexture;
    
    SoundBuffer sfxBuffer;
    Sound cursorSfx;
    
public:
    
    PauseMenu(RenderWindow* window);
    void initializeScene();
    void gameLoop(int);
    void eventHandling();
    void drawScene(int);
    void checkKeyPressed(Keyboard::Key&);
    void checkMousePosition();
    void checkMousePressed();
    void openNewWindow(int windowIndex);
    int state = 4;
    
};

#endif /* defined(__Game_frame__PauseMenu__) */
