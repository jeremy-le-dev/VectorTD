//
//  MyControlEngine.hpp
//  VectorTD
//
//  Created by Jérémy Froment on 29/09/2016.
//  Copyright © 2016 Jérémy Froment. All rights reserved.
//

#ifndef MyControlEngine_hpp
#define MyControlEngine_hpp

#include <ControlEngine.h>
#include <vector>
#include "Case.h"
#include "TowerAbstract.h"
#include "MonsterAbstract.h"
#include "Shoot.h"
#include "Game.h"

class MyControlEngine : public ControlEngine {
    std::vector<Case *> *damier;
    std::vector<TowerAbstract *> *towers;
    std::vector<MonsterAbstract *> *monsters;
    std::vector<Shoot *> *shoots;
    Game *game;

public:
    MyControlEngine(Game *game_, std::vector<Case *> *damier_, std::vector<TowerAbstract *> *towers_, std::vector<MonsterAbstract *> *monsters_, std::vector<Shoot *> *shoots_) : game(game_), damier(damier_), towers(towers_), monsters(monsters_), shoots(shoots_) {}

    virtual void MouseCallback(int button, int state, int x, int y);

    virtual void KeyboardCallback(unsigned char key, int x, int y);

    void createMonsterWithInterval(std::vector<MonsterAbstract *> &);
};

#endif /* MyControlEngine_hpp */
