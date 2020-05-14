//
//  MainMenu.h
//  Game frame
//
//  Created by Malak Sadek on 5/5/15.
//  Copyright (c) 2015 Malak Sadek. All rights reserved.
//

#ifndef __Game__MainMenu__
#define __Game__MainMenu__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ResourcePath.hpp"
#include <vector>
#include <iostream>

using namespace sf;
using namespace std;

class MainMenu
{
private:
    RenderWindow* window;
    Text titleText;
    vector<Text> menuItems;
    Font titleFont, menuItemFont;
    
    Music mainMenuMusic;
    
    Sprite backgroundPicture, soundPicture, mutePicture;
    Texture backgroundTexture, soundTexture, muteTexture;
    
    SoundBuffer sfxBuffer;
    Sound cursorSfx;
    int currentlySelectedIndex;
    
    
public:
    void stopMainMenuMusic()
    {
        mainMenuMusic.stop();
    }
    void startMainMenuMusic()
    {
        mainMenuMusic.play();
    }
    MainMenu(RenderWindow* window);
    int state;
    void initializeScene();
    void gameLoop();
    void eventHandling();
    void drawScene();
    
    void checkKeyPressed(Keyboard::Key&);
    void checkMousePosition();
    void checkMousePressed();
    int openNewWindow(int windowIndex);
    
};

#endif /* defined(__Game_frame__MainMenu__) */
