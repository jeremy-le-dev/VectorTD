//
//  MonsterAbstract.hpp
//  
//
//  Created by Jérémy Froment on 05/10/2016.
//
//

#ifndef Asteroid_hpp
#define Asteroid_hpp

#include "Game.h"
#include <vector>

class MonsterAbstract {
public:
    float posX, posY, posXBegin, posYBegin, width, height, vitesse, defaultVitesse;
    float r, g, b;
    int vie, vieFull, incrFrequence;
    bool alive;
    char oldDirection, beginDirection;
    Game *game;
    std::vector<Case *> casesUses;

    MonsterAbstract(Game *game_, float posX_ = 0.0f, float posY_ = 0.0f, float r_ = 0.0f, float g_ = 0.0f, float b_ = 0.0f, int vie_ = 200, float vitesse_ = 0.002f) :
            game(game_),
            vitesse(vitesse_),
            defaultVitesse(vitesse_),
            posX(posX_ + ((game_->gameSize / 100) / 2)),
            posY(posY_ + ((game_->gameSize / 100) / 2)),
            posXBegin(posX),
            posYBegin(posY),
            width(game_->pas - (game_->gameSize / 100)),
            height(game_->pas - (game_->gameSize / 100)),
            r(r_),
            g(g_),
            b(b_),
            vie(vie_ * game_->level / 5),
            vieFull(vie_ * game_->level / 5),
            alive(true),
            incrFrequence(0),
            oldDirection('R') {};

    virtual ~MonsterAbstract();

    virtual void draw();

    virtual void tick(char direction);

    bool checkIfAlreadyUse(Case* &case_);
};

#endif /* Asteroid_hpp */
