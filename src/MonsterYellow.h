//
// Created by Jérémy Froment on 31/10/2016.
//

#ifndef VECTORTD_MONSTERYELLOW_H
#define VECTORTD_MONSTERYELLOW_H


#include "MonsterAbstract.h"

class MonsterYellow : public MonsterAbstract {
public:
    MonsterYellow(Game *game_, float posX_, float posY_) : MonsterAbstract(game_, posX_, posY_, 1.0f, 0.992f, 0.22f, 50, 0.003f) {}

    ~MonsterYellow();
};


#endif //VECTORTD_MONSTERYELLOW_H
