//
//  Enemy.h
//  TheProject
//
//  Created by Badr AlKhamissi on 5/5/15.
//  Copyright (c) 2015 Badr AlKhamissi. All rights reserved.
//

#ifndef __Game__Enemy__
#define __Game__Enemy__

#include <stdio.h>

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include "Character.h"
#include "Player.h"
#include "CollisionHandler.h"



using namespace sf;

class Enemy: public Character{
private:
    Sprite* eSprite = new Sprite;
    Clock dir;
    Time sec;
    int i, j;
    float speed;
    const int sizeX = 80, sizeY = 80;
    float eTime;
    float iIndex, jIndex;
    bool changeDir;
    CircleShape c;
    vector<Vector2u>myPath;
public:
    Enemy(int, int);
    Enemy(const Enemy&);
    Sprite* getEnemy()const;
    void moveRandomly();
    queue<Vector2u>& getQueue();
    void attack();
    void resetPath();
    void animate();
    vector<Vector2u> getPath();
    float getX()const;
    float getY()const;
    int getI()const
    {
        return i;
    };
    int getJ()const
    {
        return j;
    };
    Time getTime()const
    {
        return sec;
    };
    float getSpeed()const
    {
        return speed;
    };
    int counter = 0;
    bool inRegion(Player& p);
    void BFS(Vector2u,Vector2u);
    void setPath(vector<Vector2u>);
    void connected(Vector2u, vector<bool>&);
    bool killHero(Player&);
    CollisionDetector detector;
    int checkSurroundings();
    bool attacking;
};

#endif /* defined(__TheProject__Enemy__) */
