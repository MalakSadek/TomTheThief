//
//  LevelHandler.cpp
//  Game
//
//  Created by Ali Sultan on 5/9/15.
//  Copyright (c) 2015 Ali Sultan. All rights reserved.
//

#include "LevelHandler.h"
#include <iostream>
#include <sstream>
using namespace std;

Level::Level(RenderWindow& window):window(window),texture("Terrain_WoodenFloor"),wTxr("Wall"),detector(40,40),keyTexture("Key"),doorTexture("Door"),
level1Music("Greed"),
level2Music("Apocalypse"),
level3Music("Sacrificial"),
keyEffect("key"),
firstLevel("Wall2")
{
    loadExtraTxrs();
}

float Level::calculateDistance(float px, float py, float qx, float qy){
    return sqrt((py-qy)*(py-qy)+(px-qx)*(px-qx));
}

void Level::loadExtraTxrs(){
    if(!gogglesTxr.loadFromFile(resourcePath()+"night_vision_goggles.png"))
        return EXIT_FAILURE;
    if(!magnetTxr.loadFromFile(resourcePath()+"magnet.png"))
        return EXIT_FAILURE;
    if(!coinTxr.loadFromFile(resourcePath()+"coin_256.png"))
        return EXIT_FAILURE;
    
    if (!font.loadFromFile(resourcePath() + "sansation.ttf"))
        return EXIT_FAILURE;
    
    if (!wonTxr.loadFromFile(resourcePath() + "comicstrip_won.png"))
        return EXIT_FAILURE;
    
    if (!lostTxr.loadFromFile(resourcePath() + "comicstrip_lost.png"))
        return EXIT_FAILURE;

    won.setTexture(wonTxr);
    lost.setTexture(lostTxr);
    won.setScale(1.2, 1.2);
    lost.setScale(1.2, 1.2);
    won.setPosition(168, 275);
    lost.setPosition(168, 275);

    coinCount = Text(":0", font, 50);
    coinCount.setColor(sf::Color::White);
    coinCount.setPosition(40*32-70, 2);
    stopWatch = Text("Time", font, 40);
    stopWatch.setColor(sf::Color::White);
    stopWatch.setPosition(20, 2);
    goggles.setTexture(gogglesTxr);
    goggles.setScale(0.5, 0.5);
    goggles.setPosition(40*32-300,10);
    magnet.setTexture(magnetTxr);
    magnet.setScale(0.2, 0.2);
    magnet.setPosition(40*32-220, 10);
    coin.setTexture(coinTxr);
    coin.setScale(0.2,0.2);
    coin.setPosition(40*32-150, 10);
    levelFinished = false;
    magnetBool = false;
}

void Level::load(int x){
    reset();
    loadMapFromFile(x);
    bfsPath = new CircleShape*[enemyNumber];
    hero.detector=detector;
    for (int i = 0; i<enemyNumber; i++) {
        enemies[i].detector = detector;
    }
    
    c.setRadius(5);
    c.setFillColor(Color::Red);
    state = x;
    if(currentLevel==1) level1Music.stop();
    if(currentLevel==2) level2Music.stop();
    if(currentLevel==3) level3Music.stop();
    currentLevel=x;
    if(x==1) level1Music.play();
    if(x==2) level2Music.play();
    if(x==3) level3Music.play();
}

int Level::getCoinsCollected()const{
    return coinsCollected;
}

void Level::run()
{
    playerTorch.goggleActive=false;
    window.clear(Color::Black);
    viewStatic.setSize(1280, 1280);
    viewStatic.setCenter(640, 640);
    if(currentLevel==1 && level1Music.paused()) level1Music.play();
    if(currentLevel==2 && level2Music.paused()) level2Music.play();
    if(currentLevel==3 && level3Music.paused()) level3Music.play();
    Event e;
    while (window.pollEvent(e))
    {
        switch (e.type)
        {
            default: break;
            case Event::LostFocus:
                state = 4;
                break;
            case Event::Closed:
                state = 4;
                break;
            case Event::KeyPressed:
                switch(e.key.code)
            {
                case Keyboard::Escape:
                    state = 4;
                    if(currentLevel==1) level1Music.pause();
                    if(currentLevel==2) level2Music.pause();
                    if(currentLevel==3) level3Music.pause();
                    break;
                default: break;
            }
                break;
        }
    }
    if(!lostLevel){
        if(Keyboard::isKeyPressed(Keyboard::Up)) hero.move(3,2);
        if(Keyboard::isKeyPressed(Keyboard::Left)) hero.move(1,2);
        if(Keyboard::isKeyPressed(Keyboard::Right)) hero.move(2,2);
        if(Keyboard::isKeyPressed(Keyboard::Down)) hero.move(4,2);
        if(Keyboard::isKeyPressed(Keyboard::Space)) playerTorch.goggleActive=true;
        else playerTorch.goggleActive=false;
        if(Keyboard::isKeyPressed(Keyboard::M) && magnetTime.getElapsedTime().asMilliseconds()>200){magnetBool=!magnetBool; magnetTime.restart();}
        if(!(Keyboard::isKeyPressed(Keyboard::Up)||Keyboard::isKeyPressed(Keyboard::Left)||Keyboard::isKeyPressed(Keyboard::Right)||Keyboard::isKeyPressed(Keyboard::Down)))
            hero.resetSpeed();
    }
  
    hero.setMagnet(magnetBool);
    
    if(!playerTorch.goggleActive)
        playerTorch.illuminate(hero.jIndex, hero.iIndex);
    else playerTorch.goggles();
    
    for(int i=0;i<coinNumber;i++)
       coins[i].dimCoin(playerTorch,calculateDistance(hero.jIndex, hero.iIndex, coins[i].getXPos()/32, coins[i].getYPos()/32), 1.2);
    
    for(int i=0;i<sizeY;i++)
        for(int j=0;j<sizeX;j++){
          if(base[i*sizeX+j].getColor().r>0)
                window.draw(*(base+(i*sizeX+j)));
          if(object[i*sizeX+j].getColor().r>0)
                window.draw(*(object+(i*sizeX+j)));
        }
    
    for(int i=0;i<coinNumber;i++){
        coins.at(i).rotate();
    }
    
    for(int i=0;i<coinNumber;i++)
    {
        if (coins[i].collectCoin(hero)) {
            coins[i].setState(true);
        }
        if (!coins[i].getState() && coins.at(i).getSprite()->getColor().r>75 && !playerTorch.goggleActive){
            window.draw(*coins[i].getSprite());
        }
    }
    
    for (int i  = 0; i<enemyNumber; i++){
        if ((enemies[i].inRegion(hero))) {
            //if (!enemies[i].attacking) {
           // if (getPath.getElapsedTime().asSeconds()>0.1) {
                enemies[i].BFS(Vector2u(enemies[i].getX()/32,enemies[i].getY()/32), Vector2u(hero.jIndex,hero.iIndex));
                *(bfsPath+i) = new CircleShape[enemies[i].getPath().size()];
               // getPath.restart();
           
            //}
        }else{
            if (!enemies[i].attacking) {
                enemies[i].moveRandomly();
            }
        }
    }
    
    for (int i = 0; i<enemyNumber; i++) {
        if (enemies[i].attacking && !wonLevel && !lostLevel) {
            enemies[i].attack();
            for (int j = 0; j<enemies[i].getPath().size(); j++) {
                bfsPath[i][j].setRadius(5);
                bfsPath[i][j].setPosition(Vector2f(enemies[i].getPath().at(j).x*32,enemies[i].getPath().at(j).y*32));
                bfsPath[i][j].setFillColor(Color(200,i*50,i*20));
            }
        }
    }

    
    int cNum = 0;
    for (int i = 0; i<coinNumber; i++) {
        if (coins[i].getState()) {
            cNum++;
        }
    }
    coinsCollected = cNum;
    

    stringstream ss;
    ss<<coinsCollected;
    coinCount.setString(ss.str());
    int sec = gameTime.getElapsedTime().asSeconds();
    int milli = gameTime.getElapsedTime().asMilliseconds();
    stringstream ss2;
    ss2<<"Time: "<<(sec/60)%60<<":"<<sec%60<<":"<<milli%1000;
    stopWatch.setString(ss2.str());
    
    window.draw(*hero.getPlayer());
    for (int i  = 0; i<enemyNumber; i++) {
        window.draw(*enemies[i].getEnemy());
    }

    if(!playerTorch.goggleActive){
        playerTorch.refreshLights();
    }else{
        window.draw(goggles);
    }
    
    if (collectKey()){
        levelFinished = true;
        animateDoor = true;
        doorTime.restart();
        hero.detector.setNonColliderObject((door.getPosition().y/32)*40+door.getPosition().x/32);
        hero.detector.setNonColliderObject(((door.getPosition().y/32))*40+(door.getPosition().x/32)+1);
        keyEffect.getSound()->play();
    }
    
    if (animateDoor) {
        if(doorTime.getElapsedTime().asSeconds()>0.2) {
            openDoor(iDoor);
            iDoor++;
            doorTime.restart();
        }
        if (iDoor>3) {
            animateDoor = false;
        }
    }
    
    if (levelFinished) {
        key.setPosition(40*32-350,10);
        key.setScale(1.5, 1.5);
    }
    if (magnetBool) {
        window.draw(magnet);
    }
    
    
    for (int i  = 0; i<enemyNumber; i++){
        if (enemies[i].killHero(hero)) {
            window.draw(lost);
            lostLevel= true;
        }
    }
    
    if (lostLevel && wonLevel) {
        for (int i = 0; i<enemyNumber; i++) {
            delete [] *(bfsPath+i);
        }
        delete bfsPath;
    }
    
    if(!lostLevel && !wonLevel){
        for (int i = 0; i<enemyNumber; i++) {
            if (enemies[i].attacking) {
                for (int j = 0; j<enemies[i].getPath().size(); j++) {
                    window.draw(bfsPath[i][j]);
                }
            }
        }
    }
    
    if(hero.getY()/32<1){
        wonLevel = true;
    }
    
    if(wonLevel){
        window.draw(won);
    }else if(!lostLevel){
        window.draw(key);
        window.draw(door);
        window.draw(coin);
        window.draw(coinCount);
        window.draw(stopWatch);
    }
}



void Level::reset(){
    window.setView(window.getDefaultView());
    gameTime.restart();
    getPath.restart();
    detector.reset();
    lostLevel = false;
    levelFinished = false;
    animateDoor = false;
    wonLevel = false;
    iDoor = 0;
    coinsCollected = 0;
    key.setScale(1, 1);
    gameTime.restart();
    while (!enemies.empty()) {
        enemies.pop_back();
    }
    while (!coins.empty()) {
        coins.pop_back();
    }
}

void Level::openDoor(int i){
    door.setTexture(*doorTexture.getTexture(i));
}

bool Level::collectKey(){
    float pX = hero.getX();
    float pY = hero.getY();
    float disX = key.getPosition().x+5 - pX;
    float disY = key.getPosition().y  - pY;

    if (sqrt(disX*disX + disY*disY )< 10 )
    {
        return true;
    }else{
        return false;
    }

}

int Level::getEnemyNumber()const{
    return enemyNumber;
}

void Level::loadMapFromFile(int x)
{
    ifstream map;
    map.open(resourcePath()+(char)(x+48)+"base.txt");
    string s;
    getline(map,s,',');
    stringstream(s)>>sizeX;
    getline(map,s,',');
    stringstream(s)>>sizeY;
    base=new Sprite[sizeX*sizeY];
    object=new Sprite[sizeX*sizeY];
    int i=0;
    int pos;
    while(!map.eof() && i<sizeY){
        for(int j=0;j<sizeX;j++){
            getline(map, s, ',');
            stringstream(s)>>pos;
            if (x==1) {
                base[i*sizeX+j].setTexture(*firstLevel.getTexture(pos));
            }else{
                base[i*sizeX+j].setTexture(*texture.getTexture(pos));
            }
            base[i*sizeX+j].setPosition(j*32, i*32);
        }
        i++;
    }
    map.close();
    map.open(resourcePath()+(char)(x+48)+"object.txt");
    i=0;
    while(!map.eof() && i<sizeY){
        for(int j=0;j<sizeX;j++){
            getline(map, s, ',');
            stringstream(s)>>pos;
            if(pos!=0){
                detector.setColliderObject(i*sizeX+j);
                if (x == 2 || x==3) {
                    object[i*sizeX+j].setTexture(*wTxr.getTexture(0));
                }else{
                    object[i*sizeX+j].setTexture(*firstLevel.getTexture(pos));
                }
                object[i*sizeX+j].setPosition(j*32, i*32);
            }
        }
        i++;
    }
    getline(map,s,',');
    if(s=="hero")
    {
        int heroX,heroY;
        getline(map,s,',');
        stringstream(s)>>heroX;
        getline(map,s,',');
        stringstream(s)>>heroY;
        hero.setPos(Vector2f(heroX*32,heroY*32));
        hero.iIndex=heroX;
        hero.jIndex=heroY;
    }
    getline(map,s,',');
    if(s=="coins")
    {
        getline(map,s,',');
        stringstream(s)>>coinNumber;
        for(int i=0;i<coinNumber;i++)
        {
            int coinX,coinY;
            getline(map,s,',');
            stringstream(s)>>coinX;
            getline(map,s,',');
            stringstream(s)>>coinY;
            Coins* newCoin = new Coins(coinX*32,coinY*32);
            coins.push_back(*newCoin);
            delete newCoin;
        }
    }
    getline(map,s,',');
    
    if(s=="enemies")
    {
        getline(map,s,',');
        stringstream(s)>>enemyNumber;
        for(int i=0;i<enemyNumber;i++){
            int enemyX,enemyY;
            getline(map,s,',');
            stringstream(s)>>enemyX;
            getline(map,s,',');
            stringstream(s)>>enemyY;
            Enemy* enemy=new Enemy(enemyX*32,enemyY*32);
            enemies.push_back(*enemy);
            delete enemy;
        }
    }
    getline(map,s,',');
    
    if(s=="door")
    {
        int doorX,doorY;
        getline(map,s,',');
        stringstream(s)>>doorX;
        getline(map,s,',');
        stringstream(s)>>doorY;
        door.setTexture(*doorTexture.getTexture(0));
        door.setPosition(Vector2f(doorX*32,doorY*32));
    }
    
    getline(map,s,',');
    
    if(s=="key")
    {
        int keyX,keyY;
        getline(map,s,',');
        stringstream(s)>>keyX;
        getline(map,s,',');
        stringstream(s)>>keyY;
        key.setTexture(*keyTexture.getTexture(0));
        key.setPosition(Vector2f(keyX*32,keyY*32));
    }
    playerTorch.setParam(base, object, sizeY, sizeX, 25, 1.15);
    map.close();
}