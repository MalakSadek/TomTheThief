//
//  Instructions.cpp
//  Game frame
//
//  Created by Malak Sadek on 5/5/15.
//  Copyright (c) 2015 Malak Sadek. All rights reserved.
//

#include "Instructions.h"
#include "MainMenu.h"
#include "CartoonWindow.h"


Instructions::Instructions(RenderWindow* window)
{
    this->window = window;
    initializeScene();
}

void Instructions::initializeScene()
{
    if (!backgroundTexture.loadFromFile(resourcePath() + "Startmenubackground.jpg"))
    {
        cout << "Error" << endl;
    }
    
    backgroundPicture.setTexture(backgroundTexture);
    backgroundPicture.setPosition(0,0);
    
    
    // Create a graphical text to display
    if (!titleFont.loadFromFile(resourcePath() + "avatar.ttf"))
    {
        cout << "ok" << endl;
    }
    
    if (!menuItemFont.loadFromFile(resourcePath() + "sansation.ttf"))
    {
        cout << "no" << endl;
    }
    
    titleText1 = Text("Instructions", titleFont, 100);
    titleText1.setColor(sf::Color::White);
    titleText1.setPosition(40, 20);
    
    instructionstext = Text("Don't let HOKO catch you!!", menuItemFont, 20);
    instructionstext.setColor(sf::Color::White);
    instructionstext.setPosition(800, 200);
    
    titleText2 = Text("Tom's Story", titleFont, 100);
    titleText2.setColor(sf::Color::White);
    titleText2.setPosition(650, 280);
    
    storytext = Text("Press 'S' to view Tom's story.", menuItemFont, 50);
    storytext.setColor(sf::Color::White);
    storytext.setPosition(560, 475);
    
    
    
    
   //Play the music
   //InstructionsMusic.play();
}

void Instructions::gameLoop(MainMenu& main)
{
    eventHandling(main);
    drawScene();
}

void Instructions::eventHandling(MainMenu& main)
{
    Event event;
    
    while(window->pollEvent(event))
    {
        switch(event.type)
        {
            case Event::Closed:
            {
                main.state = 5;
            }
                break;
            case Event::KeyPressed:
            {
            switch(event.key.code)
                {
                    case sf::Keyboard::Escape:
                    {
                        main.state = -1;
                        break;
                    }
                    case sf::Keyboard::S:
                    {
                        main.state = 5;
                        break;
                    }
                    default:
                        break;
                }
                
            }
            default:
                break;
        }
    }
}

void Instructions::drawScene()
{
    window->draw(backgroundPicture);
    window->draw(titleText1);
    window->draw(titleText2);
    window->draw(storytext);
    window->draw(instructionstext);
}

