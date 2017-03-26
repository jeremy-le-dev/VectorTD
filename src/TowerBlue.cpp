//
// Created by Jérémy Froment on 31/10/2016.
//

#include "TowerBlue.h"

/**
 * Destructor
 */
TowerBlue::~TowerBlue() {}

/**
 * Tick tower blue
 *
 * @param monsters
 * @param shoots
 */
void TowerBlue::tick(std::vector<MonsterAbstract *>* &monsters, std::vector<Shoot *>* &shoots) {
    if (incrFrequence == frequence) {
        incrFrequence = 0;
        bool shoot = false;
        int j = 0;

        while (j < monsters->size() && !shoot) {
            if (this->canShoot((*monsters)[j])) {
                shoot = true;
                shoots->push_back(new Shoot(game, posX, posY, (*monsters)[j]->posX, (*monsters)[j]->posY, r, g, b));
                (*monsters)[j]->vie = (*monsters)[j]->vie - (puissance * level);
                (*monsters)[j]->vitesse = (*monsters)[j]->vitesse / (level+1);

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
 * Return type of tower (B for blue)
 *
 * @return
 */
char TowerBlue::getType() {
    return 'B';
}
