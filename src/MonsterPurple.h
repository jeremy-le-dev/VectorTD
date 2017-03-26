//
// Created by Jérémy Froment on 31/10/2016.
//

#ifndef VECTORTD_MONSTERPURPLE_H
#define VECTORTD_MONSTERPURPLE_H


#include "MonsterAbstract.h"

class MonsterPurple : public MonsterAbstract {
public:
    MonsterPurple(Game *game_, float posX_, float posY_) : MonsterAbstract(game_, posX_, posY_, 0.988f, 0.157f, 0.988f, 100, 0.002f) {}

    ~MonsterPurple();
};


#endif //VECTORTD_MONSTERPURPLE_H
