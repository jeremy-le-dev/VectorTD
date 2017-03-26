//
// Created by Jérémy Froment on 31/10/2016.
//

#ifndef VECTORTD_TOWERBLUE_H
#define VECTORTD_TOWERBLUE_H

#include "TowerAbstract.h"

class TowerBlue : public TowerAbstract {
public:
    TowerBlue(Game *game_, float posX_, float posY_) : TowerAbstract(game_, posX_, posY_, 0.247f, 0.804f, 0.992f, 25, 1, 1, 1) {};

    ~TowerBlue();

    void tick(std::vector<MonsterAbstract *> *&, std::vector<Shoot *> *&);

    char getType();
};


#endif //VECTORTD_TOWERBLUE_H
