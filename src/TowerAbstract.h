//
// Created by Jérémy Froment on 30/10/2016.
//

#ifndef VECTORTD_TowerAbstract_H
#define VECTORTD_TowerAbstract_H

#include <vector>
#include "MonsterAbstract.h"
#include "Shoot.h"
#include "Game.h"

class TowerAbstract {
public:
    TowerAbstract(Game *game_, float posX_ = 0.0f, float posY_ = 0.0f, float r_ = 0.0f, float g_ = 0.0f, float b_ = 0.0f, int frequence_ = 50, int puissance_ = 10, int distanceShoot_ = 1, int level_ = 0) :
            game(game_),
            posX(posX_),
            posY(posY_),
            width(game_->pas),
            height(game_->pas),
            level(level_),
            r(r_),
            g(g_),
            b(b_),
            frequence(frequence_),
            puissance(puissance_),
            incrFrequence(0),
            selected(false),
            alive(true),
            distanceShoot(distanceShoot_) {};

    virtual ~TowerAbstract();

    float posX, posY, width, height;
    float r, g, b;
    int frequence, puissance, incrFrequence, distanceShoot, level;
    bool selected, alive;
    Game *game;

    virtual void draw();

    virtual void tick(std::vector<MonsterAbstract *> *&, std::vector<Shoot *> *&);

    virtual bool canShoot(MonsterAbstract *&);

    virtual char getType();
};


#endif //VECTORTD_TowerAbstract_H
