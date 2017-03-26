//
// Created by Jérémy Froment on 31/10/2016.
//

#ifndef VECTORTD_TOWERGREEN_H
#define VECTORTD_TOWERGREEN_H


#include "TowerAbstract.h"

class TowerGreen : public TowerAbstract {
public:
    TowerGreen(Game *game_, float posX_, float posY_) : TowerAbstract(game_, posX_, posY_, 0.161f, 0.992f, 0.184f, 10, 1, 1, 1) {};

    ~TowerGreen();

    char getType();
};


#endif //VECTORTD_TOWERGREEN_H
