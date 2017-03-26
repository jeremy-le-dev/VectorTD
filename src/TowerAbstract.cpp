//
// Created by Jérémy Froment on 30/10/2016.
//

#include <GraphicPrimitives.h>
#include "TowerAbstract.h"

/**
 * Draw tower
 */
void TowerAbstract::draw() {
    GraphicPrimitives::drawFillRect2D(posX + (game->pas / 4), posY + (game->pas / 4), width - (game->pas / 2), height - (game->pas / 2), r, g, b);
    GraphicPrimitives::drawOutlinedRect2D(posX, posY, width, height, r, g, b);
    
    if (selected) {
        // Zone de tir de la tourelle
        GraphicPrimitives::drawOutlinedRect2D(
                posX - distanceShoot * game->pas,
                posY - distanceShoot * game->pas,
                (distanceShoot * game->pas) + width + (distanceShoot * game->pas),
                (distanceShoot * game->pas) + height + (distanceShoot * game->pas),
                1.5f, 1.5f, 1.5f, 0.8f);
    }
    
    char* levelD = new char[6];
    sprintf(levelD, "%d", level);
    GraphicPrimitives::drawText2D(levelD, posX + (game->pas / 3), posY + (game->pas / 3), 0.0f, 0.0f, 0.0f);
}

/**
 * Tick tower
 *
 * @param monsters
 * @param shoots
 */
void TowerAbstract::tick(std::vector<MonsterAbstract *>* &monsters, std::vector<Shoot *>* &shoots) {
    if (incrFrequence == frequence) {
        incrFrequence = 0;
        bool shoot = false;
        int j = 0;

        while (j < monsters->size() && !shoot) {
            if (this->canShoot((*monsters)[j])) {
                shoot = true;
                shoots->push_back(new Shoot(game, posX, posY, (*monsters)[j]->posX, (*monsters)[j]->posY, r, g, b));
                (*monsters)[j]->vie = (*monsters)[j]->vie - (puissance * level);

                if ((*monsters)[j]->vie <= 0) {
                    (*monsters)[j]->alive = false;
                }
            }
            j++;
        }
    }

    incrFrequence++;
}

/**
 * Return true if tower can shoot monster in parameter
 *
 * @param monster
 * @return
 */
bool TowerAbstract::canShoot(MonsterAbstract* &monster) {
    return (posY - (game->pas * distanceShoot) <= monster->posY &&
            posY + height + (game->pas * distanceShoot) >= monster->posY + monster->height &&
            posX - (game->pas * distanceShoot) <= monster->posX &&
            posX + width + (game->pas * distanceShoot) >= monster->posX + monster->width);
}

/**
 * Destructor
 */
TowerAbstract::~TowerAbstract() {}

/**
 * Return type of tower
 *
 * @return
 */
char TowerAbstract::getType() {
    return 'R';
}
