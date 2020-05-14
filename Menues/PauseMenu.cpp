//
//  PauseMenu.cpp
//  Game frame
//
//  Created by Malak Sadek on 5/5/15.
//  Copyright (c) 2015 Malak Sadek. All rights reserved.
//

#include "PauseMenu.h"
#include "MainMenu.h"
#include "Instructions.h"
#include "DrawGame.h"
#include <sstream>

using namespace std;

PauseMenu::PauseMenu(RenderWindow* window)
{
    this->window = window;
    initializeScene();
}

void PauseMenu::initializeScene()
{
    if (!backgroundTexture.loadFromFile(resourcePath() + "Startmenubackground.jpg"))
    {
        cout << "Error" << endl;
    }
    
    
    backgroundPicture.setTexture(backgroundTexture);
    backgroundPicture.setPosition(0,0);
    
    if(!coinTexture.loadFromFile(resourcePath() + "coin_256.png"))
    {
        cout << "Error" << endl;
    }
    
    coinPicture.setTexture(coinTexture);
    coinPicture.setScale(0.25, 0.25);
 
    // Create a graphical text to display
    if (!titleFont.loadFromFile(resourcePath() + "avatar.ttf"))
    {
        cout << "ok" << endl;
    }
    
    if (!menuItemFont.loadFromFile(resourcePath() + "sansation.ttf"))
    {
        cout << "no" << endl;
    }
    
    titleText = Text("Paused", titleFont, 100);
    titleText.setColor(sf::Color::White);
    titleText.setPosition(40, 20);
    

    coincount = Text ("Coins Collected: 0", menuItemFont, 50);
    coincount.setColor(sf::Color::Yellow);
    
    menuItems.push_back(Text("Continue Game", menuItemFont, 50));
    menuItems.push_back(Text("Restart Game", menuItemFont, 50));
    menuItems.push_back(Text("Return to Main Menu", menuItemFont, 50));
    
    
    for(int i = 0; i<menuItems.size(); i++){
        menuItems[i].setColor(sf::Color::White);
        
        int screenWidth = window->getSize().x;
        int textWidth = menuItems[i].getLocalBounds().width;
        int textHeight = menuItems[i].getLocalBounds().height;
        
        menuItems[i].setOrigin(textWidth/2, textHeight/2);
        
        menuItems[i].setPosition(screenWidth/2 - 25, (i+2)*150);
        
        coincount.setOrigin(textWidth/2, textHeight/2);
        coincount.setPosition(screenWidth/2 + 45, 150);
        coinPicture.setPosition(screenWidth/2 - 260,135);
    }
        
    sfxBuffer.loadFromFile(resourcePath() + "Arcade_Bloop_Sound_Effect.ogg");
    cursorSfx.setBuffer(sfxBuffer);
    
    // Play the music
    currentlySelectedIndex = 0;
    menuItems[currentlySelectedIndex].setColor(Color::Yellow);
    
}

void PauseMenu::gameLoop(int coins)
{
    eventHandling();
    drawScene(coins);
}

void PauseMenu::checkKeyPressed(Keyboard::Key& key)
{
    switch(key)
    {
        case sf::Keyboard::Up:
            cursorSfx.play();
            menuItems[currentlySelectedIndex].setColor(Color::White);
            menuItems[currentlySelectedIndex].setScale(1.0, 1.0);
            currentlySelectedIndex = (currentlySelectedIndex - 1 + menuItems.size()) % menuItems.size();
            menuItems[currentlySelectedIndex].setColor(Color::Yellow);
            menuItems[currentlySelectedIndex].setScale(1.1, 1.1);
            
            break;
        case sf::Keyboard::Down:
            cursorSfx.play();
            menuItems[currentlySelectedIndex].setColor(Color::White);
            menuItems[currentlySelectedIndex].setScale(1.0, 1.0);
            currentlySelectedIndex = (currentlySelectedIndex + 1) % menuItems.size();
            menuItems[currentlySelectedIndex].setColor(Color::Yellow);
            menuItems[currentlySelectedIndex].setScale(1.1, 1.1);
            break;
        case sf::Keyboard::Return:
            switch (currentlySelectedIndex) {
                case 0:
                    state = 0;
                    break;
                case 1:
                    state = 5;
                    break;
                case 2:
                    state = -1;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void PauseMenu::openNewWindow(int windowIndex)
{
    if(windowIndex == 0)
    {
        Game game(window);
    }
    else if(windowIndex == 1)
    {
        Game game(window);
    }
    else
    {
        MainMenu menu(window);
    }
}

void PauseMenu::checkMousePosition()
{
    Vector2i mousePosition = Mouse::getPosition(*window);
    
    for(int i=0; i<menuItems.size(); i++)
    {
        IntRect boxBoundaries(menuItems[i].getPosition().x, menuItems[i].getPosition().y, menuItems[i].getLocalBounds().width, menuItems[i].getLocalBounds().height);
        if(boxBoundaries.contains(mousePosition.x, mousePosition.y))
        {
            cursorSfx.play();
            menuItems[currentlySelectedIndex].setColor(Color::White);
            menuItems[currentlySelectedIndex].setScale(1.0, 1.0);
            currentlySelectedIndex = i;
            menuItems[currentlySelectedIndex].setColor(Color::Yellow);
            menuItems[currentlySelectedIndex].setScale(1.1, 1.1);
        }
    }
    
}

void PauseMenu::checkMousePressed()
{
    Vector2i mousePosition = Mouse::getPosition(*window);
    
    for(int i=0; i<menuItems.size(); i++)
    {
        IntRect boxBoundaries(menuItems[i].getPosition().x, menuItems[i].getPosition().y, menuItems[i].getLocalBounds().width, menuItems[i].getLocalBounds().height);
        if(boxBoundaries.contains(mousePosition.x, mousePosition.y))
        {
            switch (currentlySelectedIndex) {
                case 0:
                    state = 0;
                    break;
                case 1:
                    state = 5;
                    break;
                case 2:
                    state = -1;
                    break;
                default:
                    break;
            }
        }
    }
    
}

void PauseMenu::eventHandling()
{
    Event event;
    
    while(window->pollEvent(event))
    {
        switch(event.type)
        {
            case Event::Closed:
                window->close();
                break;
            case Event::KeyPressed:
                checkKeyPressed(event.key.code);
                break;
            case Event::MouseMoved:
                checkMousePosition();
                break;
            case Event::MouseButtonPressed:
                checkMousePressed();
                break;
            default:
                break;
        }
    }
}

void PauseMenu::drawScene(int coins)
{
    window->draw(backgroundPicture);
    window->draw(titleText);
    window->draw(coincount);
    window->draw(coinPicture);
    stringstream ss;
    ss<<"Coins Collected: "<<coins;
    coincount.setString(ss.str());
    
    for (int i = 0; i < menuItems.size(); i++)
    {
        window->draw(menuItems[i]);
    }
}

