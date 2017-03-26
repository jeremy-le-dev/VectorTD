//
// Created by Jérémy Froment on 31/10/2016.
//

#ifndef VECTORTD_MONSTERRED_H
#define VECTORTD_MONSTERRED_H


#include "MonsterAbstract.h"

class MonsterRed : public MonsterAbstract {
public:
    MonsterRed(Game *game_, float posX_, float posY_) : MonsterAbstract(game_, posX_, posY_, 0.90588f, 0.29804f, 0.23529f, 100, 0.002f) {}

    ~MonsterRed();
};


#endif //VECTORTD_MONSTERRED_H
