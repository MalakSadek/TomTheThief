//
//  LevelMap.cpp
//  badr
//
//  Created by Malak Sadek on 5/8/15.
//  Copyright (c) 2015 Malak Sadek. All rights reserved.
//
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include  "Player.h"
#include  "Coins.h"
#include  "TileMap.h"
#include  "LevelMap.h"
#include  "Enemy.h"
#include  "TextureHandler.h"

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"
using namespace sf;
using namespace std;


LevelMap::LevelMap(RenderWindow* window):level1(500,900,5,5), level2(2000,2000,0,5), level3(2000,200,5,0),hero(500,500)
{
    this->window = window;
    initialiseMap();
}

void LevelMap::readMap(vector<int>&landscape, string infile){
    ifstream map;
    map.open(infile.c_str());
    string s;
    if (!map.fail()) {
        while (!map.eof()) {
            getline(map, s, ',');
            landscape.push_back(atoi(s.c_str()));
        }
    }else{
        return EXIT_FAILURE;
    }
    map.close();
}

void LevelMap::initialiseMap()
{
    if (!minimap.loadFromFile(resourcePath() + "LevelMap.png")) {
        return EXIT_FAILURE;
    }
    mini.setTexture(minimap);
    
    if (!b1.loadFromFile(resourcePath() + "thought-bubble.png")) {
        return EXIT_FAILURE;
    }
    tB1.setTexture(b1);
    
    if (!b2.loadFromFile(resourcePath() + "thought-bubble-2.png")) {
        return EXIT_FAILURE;
    }
    tB2.setTexture(b2);
    
    
    if (!b3.loadFromFile(resourcePath() + "thought-bubble-3.png")) {
        return EXIT_FAILURE;
    }
    tB3.setTexture(b3);
    
    
    // Load a music to play
    if (!music.openFromFile(resourcePath() + "forest_birds.wav")) {
        return EXIT_FAILURE;
    }
    
    position = Vector2f(gameWidth/2,gameHeight/2);
    
    vector<int>pos;
    vector<int>pos2;
    readMap(pos, resourcePath()+"layer1.csv");
    if (!layer1.load("mountain_landscape.png", sf::Vector2u(32, 32), pos, 79, 80))
        return -1;
    
    readMap(pos2, resourcePath()+"layer2.csv");
    if (!layer2.load("mountain_landscape.png", sf::Vector2u(32, 32), pos2, 79, 80))
        return -1;
    
    
    hero.setThingsPos(pos2);
    
    for (int i = 0; i<3; i++) {
        level[i] = false;
    }
    
    signal.setRadius(5);
    lS1.setRadius(5);
    lS2.setRadius(5);
    lS3.setRadius(5);
    
    signal.setFillColor(Color::Red);
    lS1.setFillColor(Color::Green);
    lS2.setFillColor(Color::Green);
    lS3.setFillColor(Color::Green);
    scale = 1;
    music.setLoop(true);
}


void LevelMap::drawMap(View& view)
{
    
    if(hero.getX()>79*32-gameWidth/2){
        position.x = 79*32-gameWidth/2;
    }else if (hero.getX()>(gameWidth/2)) {
        position.x = hero.getX();
    }else{
        position.x = gameWidth/2;
    }
    
    if (hero.getY()>79*32-gameHeight/2) {
        position.y =79*32-gameHeight/2;
    }else if (hero.getY()>(gameHeight/2)) {
        position.y = hero.getY();
    }else{
        position.y = gameHeight/2;
    }
    
    
    
    view.setCenter(position);
    window->clear();
    window->setView(view);
    
//    for (int i = 0; i<coin.size(); i++) {
//        if ((coin[i].collectCoin(hero))) {
//            coin[i].setState(true);
//        }
//    }
//    
//    for (int i = 0; i<coin.size(); i++){
//        coin[i].rotate();
//    }
//    
//    for (int i  = 0; i<10; i++) {
//        if ((hoko[i].inRegion(hero))) {
//            hoko[i].attack(hero);
//        }else{
//            hoko[i].moveRandomly();
//        }
//    }
    
//    
//    for (int i = 0; i<coin.size(); i++) {
//        //if (!(coin[i].getState())) {
//          //  window->draw(*coin[i].getSprite());
//       // }
//    }
//
    window->draw(layer1);
    window->draw(*hero.getPlayer());
//    for (int i  = 0; i<10; i++) {
//        window->draw(*hoko[i].getEnemy());
//    }
    
    window->draw(layer2);
    window->draw(*level1.getSprite());
    window->draw(*level2.getSprite());
    window->draw(*level3.getSprite());
    
    if (drawMiniMap){
        mini.setPosition((position.x)+gameWidth/2-miniMapRatio, position.y-(gameHeight/2));
        float x = mini.getPosition().x+((hero.getX()*miniMapRatio)/(79*32));
        float y = mini.getPosition().y+((hero.getY()*miniMapRatio)/(80*32));
        float x1 = mini.getPosition().x+((level1.getX()*miniMapRatio)/(79*32));
        float y1 = mini.getPosition().y+((level1.getY()*miniMapRatio)/(80*32));
        float x2 = mini.getPosition().x+((level2.getX()*miniMapRatio)/(79*32));
        float y2 = mini.getPosition().y+((level2.getY()*miniMapRatio)/(80*32));
        float x3 = mini.getPosition().x+((level3.getX()*miniMapRatio)/(79*32));
        float y3 = mini.getPosition().y+((level3.getY()*miniMapRatio)/(80*32));
        signal.setPosition(x,y);
        lS1.setPosition(x1,y1);
        lS2.setPosition(x2,y2);
        lS3.setPosition(x3,y3);
        window->draw(mini);
        window->draw(lS1);
        window->draw(lS2);
        window->draw(lS3);
        window->draw(signal);
    }
}

void LevelMap::eventHandler(View& view)
{
    sf::Event e;
    while (window->pollEvent(e))
    {
        switch (e.type)
        {
            default:break;
            case Event::LostFocus:
                state = 4;
                break;
            case Event::KeyPressed:
                switch (e.key.code)
            {
                case Keyboard::Escape:
                    state = 4;
                    break;
                case Keyboard::Return:
                    for(int i = 0; i<3; i++){
                        if (level[i]) {
                            state = i+1;
                        }
                        level[i] = false;
                    }
                    break;
                case Keyboard::Space:
                    drawMiniMap = !drawMiniMap;
                    hero.setMagnet(true);
                    break;
                case Keyboard::Z:
                    if (zoom<2) {
                        view.zoom(0.5f);
                        gameWidth/=2;
                        gameHeight/=2;
                        if(zoom == 0){
                            scale = 0.5;
                        }else{
                            scale = 0.25;
                        }
                        mini.setScale(scale,scale);
                        signal.setScale(scale,scale);
                        tB1.setScale(scale, scale);
                        tB2.setScale(scale, scale);
                        tB3.setScale(scale, scale);
                        lS1.setScale(scale, scale);
                        lS2.setScale(scale, scale);
                        lS3.setScale(scale, scale);
                        miniMapRatio/=2;
                        zoom++;
                    }
                    break;
                case Keyboard::O:
                    scale = 1;
                    gameWidth = pGW;
                    gameHeight = pGH;
                    view.setSize(gameWidth, gameHeight);
                    mini.setScale(scale,scale);
                    signal.setScale(scale,scale);
                    tB1.setScale(scale, scale);
                    tB2.setScale(scale, scale);
                    tB3.setScale(scale, scale);
                    lS1.setScale(scale, scale);
                    lS2.setScale(scale, scale);
                    lS3.setScale(scale, scale);
                    miniMapRatio = 300;
                    zoom = 0;
                    break;
                case Keyboard::Num3:
                    state = 3;
                    break;
                case Keyboard::Num2:
                    state = 2;
                    break;
                default:
                    hero.stand();
                    break;
            }
                break;
        }
    }
    
    if(Keyboard::isKeyPressed(Keyboard::Up)) hero.move(3,1);
    if(Keyboard::isKeyPressed(Keyboard::Left)) hero.move(1,1);
    if(Keyboard::isKeyPressed(Keyboard::Right)) hero.move(2,1);
    if(Keyboard::isKeyPressed(Keyboard::Down)) hero.move(4,1);
    if(!(Keyboard::isKeyPressed(Keyboard::Up)||Keyboard::isKeyPressed(Keyboard::Left)||Keyboard::isKeyPressed(Keyboard::Right)||Keyboard::isKeyPressed(Keyboard::Down)))
        hero.resetSpeed();
}

void LevelMap::gameLoop(View& view)
{
    eventHandler(view);
    drawMap(view);
    goToLevel();
}

void LevelMap::goToLevel(){
    Event e;
    if (level1.collect(hero)) {
        level1.animate();
        tB1.setPosition(hero.getX()+90*0.8*scale, hero.getY()-340*scale);
        window->draw(tB1);
        level[0] = true;
    }else if(level2.collect(hero)) {
        level2.animate();
        tB2.setPosition(hero.getX()+90*0.8*scale, hero.getY()-340*scale);
        window->draw(tB2);
        level[1] = true;
    }else if (level3.collect(hero)) {
        level3.animate();
        tB3.setPosition(hero.getX()+90*0.8*scale, hero.getY()-340*scale);
        window->draw(tB3);
        level[2] = true;
    }
}
