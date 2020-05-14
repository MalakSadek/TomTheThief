//
//  LevelMap.h
//  badr
//
//  Created by Malak Sadek on 5/8/15.
//  Copyright (c) 2015 Malak Sadek. All rights reserved.
//

#ifndef __TheProject__LevelMap__
#define __TheProject__LevelMap__

#include <stdio.h>
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
#include  "Enemy.h"
#include  "TextureHandler.h"
#include  "GlowingBall.h"
using namespace sf;
using namespace std;

class LevelMap{
public:
    LevelMap(RenderWindow* window);
    void readMap(vector<int>&,string);
    void initialiseMap();
    void eventHandler(View& view);
    void gameLoop(View&);
    void drawMap(View&);
    void goToLevel();
    int state = 0;
private:
    RenderWindow* window;
    int gameWidth = 40*32, gameHeight = 40*32;
    int pGW = gameWidth, pGH = gameHeight;
    Texture minimap;
    Sprite mini;
    Music music;
    TileMap layer1, layer2;
    bool drawMiniMap = true;
    float miniMapRatio = 300;
    int zoom = 0;
    vector<Coins>coin;
    CircleShape signal,lS1,lS2,lS3;
    levelPickUp level1,level2, level3;
    vector<Enemy>hoko;
    Player hero;
    Sprite tB1, tB2, tB3;
    Texture b1, b2, b3;
    Vector2f position;
    float scale;
    bool level[3];
};
#endif /* defined(__badr__LevelMap__) */
