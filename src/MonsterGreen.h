//
// Created by Jérémy Froment on 31/10/2016.
//

#ifndef VECTORTD_MONSTERGREEN_H
#define VECTORTD_MONSTERGREEN_H


#include "MonsterAbstract.h"

class MonsterGreen : public MonsterAbstract {
public:
    MonsterGreen(Game *game_, float posX_, float posY_) : MonsterAbstract(game_, posX_, posY_, 0.161f, 0.992f, 0.184f, 200, 0.0015f) {}

    ~MonsterGreen();
};


#endif //VECTORTD_MONSTERGREEN_H
