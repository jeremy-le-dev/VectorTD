//
//  Shoot.hpp
//  
//
//  Created by Jérémy Froment on 06/10/2016.
//
//

#ifndef Shoot_hpp
#define Shoot_hpp

#include "Game.h"

class Shoot {
public:
    Shoot(Game *game_, float posX1_ = 0.0f, float posY1_ = 0.0f, float posX2_ = 0.0f, float posY2_ = 0.0f, float r_ = 0.0f, float g_ = 0.0f, float b_ = 0.0f) :
            game(game_),
            posX1(posX1_),
            posY1(posY1_),
            posX2(posX2_),
            posY2(posY2_),
            r(r_),
            g(g_),
            b(b_),
            alive(true) {};

    ~Shoot();

    float posX1, posX2, posY1, posY2, r, g, b;
    bool alive;
    Game *game;

    void draw();
};

#endif /* Shoot_hpp */
