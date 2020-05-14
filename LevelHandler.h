//
//  LevelHandler.h
//  Game
//
//  Created by Ali Sultan on 5/9/15.
//  Copyright (c) 2015 Ali Sultan. All rights reserved.
//

#ifndef __Game__LevelHandler__
#define __Game__LevelHandler__

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "Lighting.h"
#include "Player.h"
#include "Enemy.h"
#include "ResourcePath.hpp"
#include "Coins.h"
#include <fstream>
#include "TextureHandler.h"
#include "CollisionHandler.h"
#include <vector>

class Level
{
public:
    Level(RenderWindow&);
    void load(int);
    void run();
    void loadMapFromFile(int);
    void reset();
    bool collectKey();
    int state;
    void openDoor(int);
    int getCoinsCollected()const;
    int getEnemyNumber()const;
private:
    int currentLevel;
    float calculateDistance(float px, float py, float qx, float qy);
    void loadExtraTxrs();
    View viewStatic;
    RenderWindow& window; //Pass window by reference
    int sizeX,sizeY;
    int coinNumber;
    int enemyNumber;
    Sprite* base; //declare 2 sprite layers, base and object
    Sprite* object;
    textureHandler texture, wTxr;
    textureHandler doorTexture;
    textureHandler keyTexture;
    textureHandler firstLevel;
    CollisionDetector detector;
    Player hero;
    Lightsource playerTorch;
    vector<Coins> coins;
    vector<Enemy> enemies;
    vector<int>things;
    Sprite door, key;
    int coinsCollected;
    Clock gameTime;
    Clock doorTime;
    Clock magnetTime;
    CircleShape c;
    Texture gogglesTxr, coinTxr, magnetTxr;
    Sprite goggles, coin, magnet;
    Text coinCount, stopWatch;
    Font font;
    bool levelFinished, magnetBool, animateDoor;
    int iDoor;
    Sprite won, lost;
    Texture wonTxr, lostTxr;
    bool lostLevel;
    soundHandler level1Music,level2Music,level3Music;
    soundHandler keyEffect;
    CircleShape **bfsPath;
    bool wonLevel;
    Clock getPath;
};

#endif /* defined(__Game__LevelHandler__) */
