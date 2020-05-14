//
//  Instructions.h
//  Game frame
//
//  Created by Malak Sadek on 5/5/15.
//  Copyright (c) 2015 Malak Sadek. All rights reserved.
//

#ifndef __Game__Instructions__
#define __Game__Instructions__

#include <stdio.h>
#include "Instructions.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ResourcePath.hpp"
#include <vector>
#include <iostream>
#include "MainMenu.h"


using namespace sf;
using namespace std;

class Instructions{
private:
  
    RenderWindow* window;
    
    
    Text titleText1, titleText2, instructionstext, storytext;
    Font titleFont, menuItemFont;
    
    Music InstructionsMusic;
    
    Sprite backgroundPicture;
    Texture backgroundTexture;
    
public:
    
    Instructions(RenderWindow* window);
    
    void initializeScene();
    void gameLoop(MainMenu&);
    void eventHandling(MainMenu&);
    void drawScene();
    void openNewWindow(MainMenu&);
};

#endif /* defined(__Game_frame__Instructions__) */
