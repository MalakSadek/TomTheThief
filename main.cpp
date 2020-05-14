
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <time.h>
#include  "Player.h"
#include  "Coins.h"
#include  "TileMap.h"
#include  "LevelMap.h"
#include  "Enemy.h"
#include  "TextureHandler.h"
#include  "GlowingBall.h"
#include  "MainMenu.h"
#include  "Instructions.h"
#include  "PauseMenu.h"
#include  "LevelHandler.h"
#include  "CartoonWindow.h"


// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"
using namespace sf;
using namespace std;

// Create the main window
int gameWidth = 40*32, gameHeight = 40*32;
RenderWindow window(sf::VideoMode(1722, 776), "Game");
RenderWindow gameWindow(sf::VideoMode(gameWidth, gameHeight), "Game");
View view(sf::FloatRect(0,0, gameWidth, gameHeight));


int main(int, char const**)
{
    int levelSelector = -1;
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    gameWindow.setVerticalSyncEnabled(true);
    gameWindow.setFramerateLimit(60);
    Level level(gameWindow);
    gameWindow.close();
    LevelMap lMap(&gameWindow);
    MainMenu menu(&window);
    PauseMenu pause(&window);
    Instructions inst(&window);
    Cartoon cartoon(&window);
    srand(unsigned(time(NULL)));
    bool levelLoad = false;
    bool flag = false;
    int tmpLevel = 0;
    int coinsCollected = 0;
    while (!flag) {
        while (window.isOpen()) {
            window.clear();
            switch (levelSelector) {
                case -1:
                    menu.gameLoop();
                    break;
                case 1:
                    inst.gameLoop(menu);
                    break;
                case 2:
                    flag = true;
                    window.close();
                    break;
                case 4:
                    pause.gameLoop(coinsCollected);
                    if(pause.state == -1){
                        menu.state = -1;
                    }else if (pause.state == 5){
                        levelLoad = false;
                        pause.state = 0;
                    }
                    break;
                case 5:
                    cartoon.gameloop(menu);
                    break;
                default:
                    break;
            }
            levelSelector = menu.state;
            if (levelSelector == 0 || pause.state == 0) {
                menu.stopMainMenuMusic();
                window.close();
                if (menu.state!=0) {
                    lMap.state = tmpLevel;
                    level.state = tmpLevel;
                }else{
                    lMap.state = 0;
                }
                gameWindow.create(sf::VideoMode(gameWidth, gameHeight), "Game");
            }else{
                window.display();
            }
        }
        
        while (gameWindow.isOpen()) {
            view.setCenter(gameWidth/2, gameHeight/2);
            gameWindow.setView(view);
            levelSelector = lMap.state;
            if (levelSelector == -1) {
                gameWindow.close();
                if (menu.state!=4) {
                    menu.state = -1;
                }
                window.create(sf::VideoMode(1722, 776), "Main Menu");
            }
            switch (levelSelector) {
                case 0:
                    lMap.gameLoop(view);
                    levelLoad = false;
                    tmpLevel = 0;
                    break;
                case 1:
                    if (!levelLoad) {
                        level.load(1);
                        levelLoad = true;
                    }
                    level.run();
                    lMap.state = level.state;
                    tmpLevel = 1;
                    break;
                case 2:
                    if (!levelLoad) {
                        level.load(2);
                        levelLoad = true;
                    }
                    level.run();
                    lMap.state = level.state;
                    tmpLevel = 2;
                    break;
                case 3:
                    if (!levelLoad) {
                        level.load(3);
                        levelLoad = true;
                    }
                    level.run();
                    lMap.state = level.state;
                    tmpLevel = 3;
                    break;
                case 4:
                    menu.state = 4;
                    menu.startMainMenuMusic();
                    pause.state = 4;
                    lMap.state = -1;
                    break;
                default:
                    break;
            }
            coinsCollected = level.getCoinsCollected();
            gameWindow.display();
        }
    }
    return EXIT_SUCCESS;
}
