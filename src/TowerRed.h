//
//  Tower.hpp
//  
//
//  Created by Jérémy Froment on 05/10/2016.
//
//

#ifndef VECTORTD_TOWERRED_H
#define VECTORTD_TOWERRED_H


#include "TowerAbstract.h"

class TowerRed : public TowerAbstract {
public:
    TowerRed(Game *game_, float posX_, float posY_) : TowerAbstract(game_, posX_, posY_, 0.90588f, 0.29804f, 0.23529f, 50, 7, 1, 1) {};

    ~TowerRed();

    void tick(std::vector<MonsterAbstract *> *&, std::vector<Shoot *> *&);

    char getType();
};

#endif // VECTORTD_TOWERRED_H
