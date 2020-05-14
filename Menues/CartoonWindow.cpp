//
//  CartoonWindow.cpp
//  Game frame
//
//  Created by Malak Sadek on 5/5/15.
//  Copyright (c) 2015 Malak Sadek. All rights reserved.
//

#include "CartoonWindow.h"
#include "Instructions.h"

Cartoon::Cartoon(RenderWindow* window)
{
    this->window = window;
    initializeScene();
}

void Cartoon::initializeScene()
{
    if (!backgroundTexture.loadFromFile(resourcePath() + "cartoon.png"))
    {
        cout << "Error" << endl;
    }
    
    backgroundPicture.setTexture(backgroundTexture);
    backgroundPicture.setPosition(150,0);
    backgroundPicture.setScale(1.6, 1.28);
}

void Cartoon::gameloop(MainMenu& main)
{
    eventHandling(main);
    drawScene();
}

void Cartoon::eventHandling(MainMenu& main)
{
    Event event;
    while(window->pollEvent(event))
    {
        switch(event.type)
        {
            case Event::Closed:
            {
                main.state = 1;
                
            }
                break;
            case Event::KeyPressed:
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::Escape:
                    {
                        main.state = 1;
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

void Cartoon::drawScene()
{
    window->draw(backgroundPicture);
}


