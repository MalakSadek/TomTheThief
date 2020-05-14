//
//  Enemy.cpp
//  TheProject
//
//  Created by Badr AlKhamissi on 5/5/15.
//  Copyright (c) 2015 Badr AlKhamissi. All rights reserved.
//

#include "Enemy.h"
#include "ResourcePath.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <ctime>



#include "TextureHandler.h"

using namespace std;
using namespace sf;

textureHandler enemyTxr("Enemy");

Enemy::Enemy(int x, int y):detector(40,40){
    i = 0;
    j = 2;
    srand(unsigned(time(NULL)));
    speed = 0.1;
    eTime = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/0.5) +0.3;
    eSprite->setTexture(*enemyTxr.getTexture(j));
    eSprite->setPosition(x,y);
    eSprite->setScale(0.5, 0.5);
    eSprite->setOrigin(80*0.5, 80*0.5);
    dir.restart();
    changeDir = false;
    counter = 0;
}

Enemy::Enemy(const Enemy& rhs):detector(40,40)
{
    i=rhs.getI();
    j=rhs.getJ();
    speed=rhs.getSpeed();
    eTime = static_cast <float> (rand()) / static_cast <float> (RAND_MAX/0.5) +0.3; // Changed
    eSprite=rhs.getEnemy();
    dir.restart();
    changeDir = false;
    counter = 0;
}

void Enemy::moveRandomly(){
    sec = dir.getElapsedTime();
    speed = 0.2;

    // if(changeDir){
    //     j = rand()%4;
    //     changeDir = false;
    //  }
    
    //    if (sec.asSeconds()>eTime) {
    //        dir.restart();
    //        j = rand()%4;
    //    }

    jIndex=getX()/32;
    iIndex=(getY())/32;

//        if (j == 2){
//            if (!detector.hasCollided(iIndex, jIndex+1)&&!detector.hasCollided(iIndex, jIndex+2)) {
//                eSprite->move(speed, 0);
//            }else{
//                while (j==2) {
//                    j = rand()%4;
//                }
//            }
//        }else if(j == 1){
//            if (!detector.hasCollided(iIndex,jIndex-1)&&!detector.hasCollided(iIndex, jIndex-2)) {
//                eSprite->move(-speed, 0);
//            }else{
//                while (j==1) {
//                    j = rand()%4;
//                }
//            }
//        }else if(j == 0){
//            if (!detector.hasCollided(iIndex+1,jIndex)&&!detector.hasCollided(iIndex+2, jIndex))  {
//                eSprite->move(0, speed);
//            }else{
//                while (j==0) {
//                    j = rand()%4;
//                }
//            }
//        }else if(j == 3){
//            if (!detector.hasCollided(iIndex-1,jIndex)&&!detector.hasCollided(iIndex-2, jIndex))  {
//                eSprite->move(0, -speed);
//            }else{
//                while (j==3) {
//                    j = rand()%4;
//                }
//            }
//        }
//    
    
//    if (j == 0){
//        if (detector.hasCollided(iIndex, jIndex+2)) {
//            eSprite->move(0, speed);
//            j = rand()%2 ? 2:3;
//        }    }else if(j == 3){
//        if (detector.hasCollided(iIndex,jIndex-2)) {
//            eSprite->move(0, -speed);
//            j = rand()%2 ? 2:0;
//        }
//    }else if(j == 2){
//        if (detector.hasCollided(iIndex+2,jIndex))  {
//            eSprite->move(speed, 0);
//            j = rand()%2 ? 3:1;
//        }
//    }else if(j == 1){
//        if (detector.hasCollided(iIndex-2,jIndex))  {
//            eSprite->move(-speed, 0);
//            j = rand()%2 ? 3:2;
//        }
//    }
    
    
    if (iIndex<39 && jIndex<39 && iIndex>=0 && jIndex >=0) {
        
        if(sec.asSeconds()>eTime){
            j = checkSurroundings();
            dir.restart();
       }
        
        switch (j) {
            case 0:
                eSprite->move(0, speed);
                break;
            case 1:
                eSprite->move(-speed,0);
                break;
            case 2:
                eSprite->move(speed,0);
                break;
            case 3:
                eSprite->move(0, -speed);
                break;
            default:
                break;
        }
    }
    

    //  //  cout<<j<<endl;
    
    //    if (j == 0) {
    //        if (!(collision(getTileNumber2(getX(), getY()+32+80, 0)))) {
    //            eSprite->move(0, speed);
    //        }else{
    //            j = rand()%4;
    //        }
    //    }else if(j==3){
    //        if (!(collision(getTileNumber2(getX(), getY()-32, 0)))) {
    //            eSprite->move(0, -speed);
    //        }else{
    //            j = rand()%4;
    //        }
    //    }else if(j==2){
    //        if (!(collision(getTileNumber2(getX()+32+80, getY(), 0)))) {
    //            eSprite->move(speed, 0);
    //        }else{
    //            j = rand()%4;
    //        }
    //    }else if(j==1){
    //        if (!(collision(getTileNumber2(getX()-32, getY(), 0)))) {
    //            eSprite->move(-speed, 0);
    //        }else{
    //            j = rand()%4;
    //        }
    //    }
    animate();
}

int Enemy::checkSurroundings(){
    jIndex=getX()/32;
    iIndex=getY()/32;
    srand(unsigned(time(NULL)));

    int dir[4] = {0,0,0,0};
    // 0: DOWN
    // 1: LEFT
    // 2: RIGHT
    // 3: UP

    if (!detector.hasCollided(iIndex+1, jIndex)) {
        dir[0]++;
    }
    if (!detector.hasCollided(iIndex-1, jIndex)) {
        dir[3]++;
    }
    if (!detector.hasCollided(iIndex+1, jIndex+1)) {
        dir[2]++;
        dir[0]++;
    }
    if (!detector.hasCollided(iIndex-1, jIndex-1)) {
        dir[3]++;
        dir[1]++;
    }
    if (!detector.hasCollided(iIndex-1, jIndex+1)) {
        dir[3]++;
        dir[2]++;
    }
    if (!detector.hasCollided(iIndex+1, jIndex-1)) {
        dir[1]++;
        dir[0]++;
    }
    if (!detector.hasCollided(iIndex, jIndex+1)) {
        dir[2]++;
    }
    if (!detector.hasCollided(iIndex, jIndex-1)) {
        dir[1]++;
    }
    
    
    if (!detector.hasCollided(iIndex+2, jIndex)) {
        dir[0]++;
    }
    if (!detector.hasCollided(iIndex-2, jIndex)) {
        dir[3]++;
    }
    if (!detector.hasCollided(iIndex+2, jIndex+2)) {
        dir[2]++;
        dir[0]++;
    }
    if (!detector.hasCollided(iIndex-2, jIndex-2)) {
        dir[3]++;
        dir[1]++;
    }
    if (!detector.hasCollided(iIndex-2, jIndex+2)) {
        dir[3]++;
        dir[2]++;
    }
    if (!detector.hasCollided(iIndex+2, jIndex-2)) {
        dir[1]++;
        dir[0]++;
    }
    if (!detector.hasCollided(iIndex, jIndex+2)) {
        dir[2]++;
    }
    if (!detector.hasCollided(iIndex, jIndex-2)) {
        dir[1]++;
    }
    
    int min = 0;
    for (int i = 1; i<4; i++) {
        if (dir[i] == dir[min]) {
            min = rand()%2 ? min:i;
        }else if (dir[i]>dir[min]) {
            min = i;
        }
    }

    return min;
}


bool Enemy::inRegion(Player& p){
    float pX = p.getPlayer()->getPosition().x;
    float pY = p.getPlayer()->getPosition().y;
    float disX = getX() - pX;
    float disY = getY() - pY;
    
    if (sqrt(pow(disX, 2) + pow(disY, 2)) < 500 )
    {
        return true;
    }else{
        return false;
    }
}


bool Enemy::killHero(Player& p){
    float pX = p.getX();
    float pY = p.getY();
    float disX = getX()- pX;
    float disY = getY()- pY;
    
    if (sqrt(pow(disX, 2) + pow(disY, 2)) < 20 )
    {
        return true;
    }else{
        return false;
    }
}

void Enemy::attack(){
    if(counter<myPath.size()){
        speed = 1;
        Vector2u target = myPath[counter];
    if (getX()/32>1 && getY()/32>1 && getX()/32<39 && getY()/32<39) {
        
       if (abs(target.x-getX()/32)<=abs(target.y-getY()/32)) {
           
           
            if (target.y>getY()/32){
                eSprite->move(0, speed);
                j = 3;
            }else if(target.y<getY()/32){
                eSprite->move(0, -speed);
                j = 0;
            }
       }else{
//            else if (target.x>getX()/32) {
//                eSprite->move(speed, 0);
//                j = 2;
//            }else if(target.x<getX()/32){
//                eSprite->move(-speed,0);
//                j = 1;
//            }
             if (target.x>getX()/32) {
                eSprite->move(speed, 0);
                j = 2;
            }else if(target.x<getX()/32){
                eSprite->move(-speed,0);
                j = 1;
            }
//            else if (target.y<getY()/32){
//                eSprite->move(0, -speed);
//                j = 3;
//            }else if(target.y>getY()/32){
//                eSprite->move(0, speed);
//                j = 0;
            }
        
        int xx=getX()/32,yy=getY()/32;
        if(target == Vector2u(xx, yy)){
            counter++;
        }
    }else{
        attacking = false;
        counter = 0;
    }
    animate();
    }
}

void Enemy::setPath(vector<Vector2u>path){
    for (int i = 0; i<path.size(); i++) {
        myPath.push_back(path[i]);
    }
}

void Enemy::resetPath(){
    counter = 0; // Changed
    while (!myPath.empty()) {
        myPath.pop_back();
    }
}

vector<Vector2u> Enemy::getPath(){
    return myPath;
}

void Enemy::BFS(Vector2u s, Vector2u hero){
    if (s!=hero) {
        vector<bool>visited;
        struct state{
            Vector2u position;
            vector<Vector2u> path;
        };
        queue<state>q;
        state st;
        st.position=s;
        bool flag = false;
        for (int i = 0; i<40; i++) {
            for (int j = 0; j<40; j++) {
                visited.push_back(false);
            }
        }
        q.push(st);
        visited[s.y*40+s.x] = true;
        while (!q.empty() && !flag) {
            state tmp = q.front();
            q.pop();
            if (tmp.position == hero) {
                flag = true;
                attacking = true;
                resetPath();
                setPath(tmp.path);
//                for(int k=0;k<tmp.path.size();k++)
//                    cout<<tmp.path[k].x<<" "<<tmp.path[k].y<<endl;
//                cout<<endl;
            }else{
                Vector2u p=tmp.position;
                state psh = tmp;
                if (!(detector.hasCollided(p.y+1,p.x)) && !visited[(p.y+1)*40+p.x]) {
                    psh.position=Vector2u(p.x,p.y+1);
                    psh.path.push_back(Vector2u(p.x,p.y+1));
                    q.push(psh);
                    visited[(p.y+1)*40+p.x] = true;
                }
                psh=tmp;
                if (!((detector.hasCollided(p.y,p.x+1))) && !visited[(p.y)*40+(p.x+1)]) {
                    psh.position =Vector2u(p.x+1,p.y);
                    psh.path.push_back(Vector2u(p.x+1,p.y));
                    q.push(psh);
                    visited[(p.y)*40+(p.x+1)] = true;
                }
                psh=tmp;
                if (!(detector.hasCollided(p.y-1,p.x)) && !visited[(p.y-1)*40+p.x]) {
                    psh.position =Vector2u(p.x,p.y-1);
                    psh.path.push_back(Vector2u(p.x,p.y-1));
                    q.push(psh);
                    visited[(p.y-1)*40+p.x] = true;
                }
                psh=tmp;
                
                if (!(detector.hasCollided(p.y,p.x-1)) && !visited[(p.y)*40+(p.x-1)]) {
                    psh.position =Vector2u(p.x-1,p.y);
                    psh.path.push_back(Vector2u(p.x-1,p.y));
                    q.push(psh);
                    visited[(p.y)*40+(p.x-1)] = true;
                }
            }
        }
    }
}

void Enemy::animate(){
    if (i==3) {
        i = 0;
    }else{
        i++;
    }
    eSprite->setTexture(*enemyTxr.getTexture(j+i*4));
}

float Enemy::getX()const{
    return eSprite->getPosition().x;
}

float Enemy::getY()const{
    return eSprite->getPosition().y;
}

Sprite* Enemy::getEnemy()const{
    return eSprite;
}