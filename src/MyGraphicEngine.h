//
//  MyGraphicEngine.hpp
//  
//
//  Created by Jérémy Froment on 29/09/2016.
//
//

#ifndef MyGraphicEngine_hpp
#define MyGraphicEngine_hpp

#include <GraphicEngine.h>
#include "Case.h"
#include "TowerAbstract.h"
#include "MonsterAbstract.h"
#include "Shoot.h"
#include "Game.h"

class MyGraphicEngine : public GraphicEngine {
    std::vector<Case *> *damier;
    std::vector<TowerAbstract *> *towers;
    std::vector<MonsterAbstract *> *monsters;
    std::vector<Shoot *> *shoots;
    Game *game;

public:
    MyGraphicEngine(Game *game_, std::vector<Case *> *damier_, std::vector<TowerAbstract *> *towers_, std::vector<MonsterAbstract *> *monsters_, std::vector<Shoot *> *shoots_) : game(game_), damier(damier_), towers(towers_), monsters(monsters_), shoots(shoots_) {}

    virtual void Draw();

    virtual void reshape(int width, int height);
};

#endif /* MyGraphicEngine_hpp */
