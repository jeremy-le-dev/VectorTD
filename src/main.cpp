//
//  main.cpp
//  VectorTD
//
//  Created by Jérémy Froment on 29/09/2016.
//

#include <Engine.h>
#include "Game.h"
#include "Case.h"
#include "TowerAbstract.h"
#include "MonsterAbstract.h"
#include "Shoot.h"
#include "MyGraphicEngine.h"
#include "MyGameEngine.h"
#include "MyControlEngine.h"

/**
 * Main application
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char * argv[]) {
    std::vector<Case *> damier;
    std::vector<TowerAbstract *> towers;
    std::vector<MonsterAbstract *> monsters;
    std::vector<Shoot *> shoots;

    Game game(800, 700);
    Engine e(argc, argv, game.width, game.height, new char[10] {'V', 'E', 'C', 'T', 'O', 'R', ' ', 'T', 'D', '\0'});
    GraphicEngine * ge = new MyGraphicEngine(&game, &damier, &towers, &monsters, &shoots);
    GameEngine * gme   = new MyGameEngine(&game, &damier, &towers, &monsters, &shoots);
    ControlEngine * ce = new MyControlEngine(&game, &damier, &towers, &monsters, &shoots);

    e.setGraphicEngine(ge);
    e.setGameEngine(gme);
    e.setControlEngine(ce);

    e.start();

    return EXIT_SUCCESS;
}
