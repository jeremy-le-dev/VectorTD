//
//  MyGameEngine.hpp
//  
//
//  Created by Jérémy Froment on 29/09/2016.
//
//

#ifndef MyGameEngine_hpp
#define MyGameEngine_hpp

#include <GameEngine.h>
#include <vector>
#include "Case.h"
#include "TowerAbstract.h"
#include "MonsterAbstract.h"
#include "Shoot.h"
#include "Game.h"

class MyGameEngine : public GameEngine {
    std::vector<Case *> *damier;
    std::vector<TowerAbstract *> *towers;
    std::vector<MonsterAbstract *> *monsters;
    std::vector<Shoot *> *shoots;
    Game *game;

public:
    MyGameEngine(Game *game_, std::vector<Case *> *damier_, std::vector<TowerAbstract *> *towers_, std::vector<MonsterAbstract *> *monsters_, std::vector<Shoot *> *shoots_) : game(game_), damier(damier_), towers(towers_), monsters(monsters_), shoots(shoots_) {}

    virtual void idle();
};

#endif /* MyGameEngine_hpp */
