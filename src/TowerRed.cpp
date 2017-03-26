//
//  Created by Jérémy Froment on 05/10/2016.
//

#include "TowerRed.h"

/**
 * Destructor
 */
TowerRed::~TowerRed() {}

/**
 * Return type of tower (R for red)
 *
 * @return
 */
char TowerRed::getType() {
    return 'R';
}

/**
 * Tick tower
 *
 * @param monsters
 * @param shoots
 */
void TowerRed::tick(std::vector<MonsterAbstract *>* &monsters, std::vector<Shoot *>* &shoots) {
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

                int s = 0;
                while (s < monsters->size()) {
                    if ((*monsters)[j]->posY - (*monsters)[j]->height - (game->pas) <= (*monsters)[s]->posY &&
                        (*monsters)[j]->posY + (*monsters)[j]->height + (game->pas) >= (*monsters)[s]->posY + (*monsters)[s]->height &&
                        (*monsters)[j]->posX - (*monsters)[j]->width - (game->pas) <= (*monsters)[s]->posX &&
                        (*monsters)[j]->posX + (*monsters)[j]->width + (game->pas) >= (*monsters)[s]->posX + (*monsters)[s]->width
                        && (*monsters)[j] != (*monsters)[s]) {

                        shoots->push_back(new Shoot(game, (*monsters)[j]->posX, (*monsters)[j]->posY, (*monsters)[s]->posX, (*monsters)[s]->posY, r, g, b));
                        (*monsters)[s]->vie = (*monsters)[s]->vie - ((puissance * level) / 2);

                        if ((*monsters)[s]->vie <= 0) {
                            (*monsters)[s]->alive = false;
                        }
                    }
                    s++;
                }
            }
            j++;
        }
    }

    incrFrequence++;
}
