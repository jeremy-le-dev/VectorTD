//
// Created by Jérémy Froment on 29/09/2016.
//

#ifndef Case_hpp
#define Case_hpp

#include "Game.h"
#include "TowerAbstract.h"

class Case {
public:
    Case(Game *game_, float posX_ = 0.0f, float posY_ = 0.0f) :
            game(game_),
            posX(posX_),
            posY(posY_),
            width(game_->pas),
            height(game_->pas),
            r(0.106f),
            g(0.282f),
            b(0.282f),
            haveTower(false),
            tower(NULL),
            isBegin(false),
            isEnd(false),
            isPath(false) {};

    ~Case();

    float posX, posY, width, height, r, g, b, a;
    int coordX, coordY;
    bool isPath, haveTower, isBegin, isEnd;
    Game *game;
    TowerAbstract *tower;

    void draw();

    void tick();

    void setRGB(float r_, float g_, float b_);

    float getPosX();

    float getPosY();

    bool touch(float x, float y);
};

#endif /* Case_hpp */
