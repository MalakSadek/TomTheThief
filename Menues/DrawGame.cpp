//
//  DrawGame.cpp
//  Game frame
//
//  Created by Malak Sadek on 5/5/15.
//  Copyright (c) 2015 Malak Sadek. All rights reserved.
//

#include "DrawGame.h"
#include "PauseMenu.h"


Game::Game(RenderWindow* window)
{
    this->window = window;
    initializeScene();
    gameLoop();
    
}

void Game::initializeScene()
{
    
   backgroundTexture.loadFromFile(resourcePath() + "images-2.jpeg");
   backgroundPicture.setTexture(backgroundTexture);
   backgroundPicture.setPosition(0,0);

}

void Game::eventHandling()
{
    Event event;
    
    while(window->pollEvent(event))
    {
        switch(event.type)
        {
            case Event::Closed:
            {
                window->close();
                break;
            }
            case Event::KeyPressed:
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::Escape:
                    {
                        PauseMenu pause(window);
                        window->close();
                        
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

void Game::gameLoop()
{
    while(window->isOpen())
    {
        eventHandling();
        drawScene();
    }
}

void Game::drawScene()
{
    window->clear();
    window->draw(backgroundPicture);
    window->display();
}
