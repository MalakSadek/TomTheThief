//
//  MainMenu.cpp
//  Game frame
//
//  Created by Malak Sadek on 5/5/15.
//  Copyright (c) 2015 Malak Sadek. All rights reserved.
//

#include "MainMenu.h"
#include "Instructions.h"
#include "DrawGame.h"
#include "LevelMap.h"


MainMenu::MainMenu(RenderWindow* window)
{
    this->window = window;
    initializeScene();
    state = -1;
}

void MainMenu::initializeScene()
{
    if (!backgroundTexture.loadFromFile(resourcePath() + "Startmenubackground.jpg"))
    {
        cout << "Error" << endl;
    }
    
    soundTexture.loadFromFile(resourcePath() + "SpeakerIcon__13563_zoom.png");
    muteTexture.loadFromFile(resourcePath() + "audio-mute.png");
    
    backgroundPicture.setTexture(backgroundTexture);
    soundPicture.setTexture(soundTexture);
    mutePicture.setTexture(muteTexture);
    backgroundPicture.setPosition(0,0);
    soundPicture.setPosition(20, 650);
    soundPicture.setScale(0.25, 0.25);
    mutePicture.setPosition(20,650);
    mutePicture.setScale(0.25, 0.25);
    
    
    // Create a graphical text to display
    if (!titleFont.loadFromFile(resourcePath() + "avatar.ttf"))
    {
        cout << "ok" << endl;
    }
    
    if (!menuItemFont.loadFromFile(resourcePath() + "sansation.ttf"))
    {
        cout << "no" << endl;
    }
    
    titleText = Text("Tom The Thief!", titleFont, 100);
    titleText.setColor(sf::Color::White);
    titleText.setPosition(40, 20);
    
    menuItems.push_back(Text("(1) Start a new game", menuItemFont, 50));
    menuItems.push_back(Text("(2) Instructions & Story", menuItemFont, 50));
    menuItems.push_back(Text("(3) Exit", menuItemFont, 50));
    
    
    for(int i = 0; i<menuItems.size(); i++){
        menuItems[i].setColor(sf::Color::White);
        
        int screenWidth = window->getSize().x;
        int textWidth = menuItems[i].getLocalBounds().width;
        int textHeight = menuItems[i].getLocalBounds().height;
        
        menuItems[i].setOrigin(textWidth/2, textHeight/2);
        
        menuItems[i].setPosition(screenWidth/2, (i+2)*150);
    }
    
    if (!mainMenuMusic.openFromFile(resourcePath() + "Dramatic_music.ogg"))
    {
        cout << "no" << endl;
    }
    
    sfxBuffer.loadFromFile(resourcePath() + "Arcade_Bloop_Sound_Effect.ogg");
    cursorSfx.setBuffer(sfxBuffer);
    
    // Play the music
    mainMenuMusic.setLoop(true);
    mainMenuMusic.setVolume(50);
    mainMenuMusic.play();
    
    currentlySelectedIndex = 0;
    menuItems[currentlySelectedIndex].setColor(Color::Yellow);
}

void MainMenu::gameLoop()
{
    eventHandling();
    drawScene();
}

void MainMenu::checkKeyPressed(Keyboard::Key& key)
{
    cursorSfx.play();
    switch(key)
    {
        case sf::Keyboard::Up:
            menuItems[currentlySelectedIndex].setColor(Color::White);
            menuItems[currentlySelectedIndex].setScale(1.0, 1.0);
            currentlySelectedIndex = (currentlySelectedIndex - 1 + menuItems.size()) % menuItems.size();
            menuItems[currentlySelectedIndex].setColor(Color::Yellow);
            menuItems[currentlySelectedIndex].setScale(1.1, 1.1);
            
            break;
        case sf::Keyboard::Down:
            menuItems[currentlySelectedIndex].setColor(Color::White);
            menuItems[currentlySelectedIndex].setScale(1.0, 1.0);
            currentlySelectedIndex = (currentlySelectedIndex + 1) % menuItems.size();
            menuItems[currentlySelectedIndex].setColor(Color::Yellow);
            menuItems[currentlySelectedIndex].setScale(1.1, 1.1);
            break;
        case sf::Keyboard::Return:
        {
            mainMenuMusic.stop();
            state = currentlySelectedIndex;
           break;
        }
        case sf::Keyboard::Escape:
            window->close();
            break;
        case sf::Keyboard::Num1:
            openNewWindow(0);
            break;
        case sf::Keyboard::Num2:
            openNewWindow(1);
            break;
        case sf::Keyboard::Num3:
            window->close();
            break;
        default:
            break;
    }
}

int MainMenu::openNewWindow(int windowIndex)
{
    if(windowIndex == 0)
    {
        mainMenuMusic.stop();
        Instructions instructions(window);
    }
    else if(windowIndex == 1)
    {
        mainMenuMusic.stop();
        Instructions Instructions(window);
        return 1;
    }
}

void MainMenu::checkMousePosition()
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

void MainMenu::checkMousePressed()
{
    Vector2i mousePosition = Mouse::getPosition(*window);
    
    for(int i=0; i<menuItems.size(); i++)
    {
        IntRect boxBoundaries(menuItems[i].getPosition().x, menuItems[i].getPosition().y, menuItems[i].getLocalBounds().width, menuItems[i].getLocalBounds().height);
        if(boxBoundaries.contains(mousePosition.x, mousePosition.y))
        {
            state = currentlySelectedIndex;
        }
    }
    
}

void MainMenu::eventHandling()
{
    Event event;
    IntRect muteBoundaries(soundPicture.getPosition().x, soundPicture.getPosition().y, soundPicture.getLocalBounds().width, soundPicture.getLocalBounds().height);
    Vector2i mousePosition = Mouse::getPosition(*window);
    
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
      
        if((muteBoundaries.contains(mousePosition.x, mousePosition.y))&&(Mouse::isButtonPressed(sf::Mouse::Left))&&(mainMenuMusic.getVolume() == 100))
        {
            mainMenuMusic.setVolume(0);
        }
        else if((muteBoundaries.contains(mousePosition.x, mousePosition.y))&&(Mouse::isButtonPressed(sf::Mouse::Left))&&(mainMenuMusic.getVolume() == 0))
        {
            mainMenuMusic.setVolume(100);
        }
    }
}

void MainMenu::drawScene()
{
    window->draw(backgroundPicture);
    window->draw(titleText);
    if(mainMenuMusic.getVolume() == 100)
    window->draw(soundPicture);
    if(mainMenuMusic.getVolume() == 0)
    window->draw(mutePicture);
    for (int i = 0; i < menuItems.size(); i++){
        window->draw(menuItems[i]);
    }
}
