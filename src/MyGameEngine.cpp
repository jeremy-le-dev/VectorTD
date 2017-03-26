//
//  MyGameEngine.cpp
//  
//
//  Created by Jérémy Froment on 29/09/2016.
//
//

#include <iostream>
#include "MyGameEngine.h"

/**
 * Call on tick
 */
void MyGameEngine::idle() {
    if (game->started) {
        if (!game->mypath) {
            if (!game->inPause && !game->gameover) {
                if (game->vie <= 0) {
                    game->gameover = true;
                }

                for (int i = 0; i < towers->size(); i++) {
                    (*towers)[i]->tick(monsters, shoots);
                    (*towers)[i]->selected = (*towers)[i]->posX == game->currentTower->posX && (*towers)[i]->posY == game->currentTower->posY;
                }

                if (monsters->size() > 0) {
                    for (int m = 0; m < monsters->size(); m++) {
                        char direction = (*monsters)[m]->oldDirection;

                        for (int i = 0; i < damier->size(); i++) {
                            if ((*damier)[i]->isPath
                                && (*damier)[i]->posX <= (*monsters)[m]->posX
                                && (*damier)[i]->posX + (*damier)[i]->width >= (*monsters)[m]->posX + (*monsters)[m]->width
                                && (*damier)[i]->posY <= (*monsters)[m]->posY
                                && (*damier)[i]->posY + (*damier)[i]->height >= (*monsters)[m]->posY + (*monsters)[m]->height) {

                                if ((*damier)[i]->isEnd) {
                                    direction = 'E';
                                } else {
                                    for (int j = 0; j < damier->size(); j++) {
                                        if ((*damier)[j]->isBegin && (!(*monsters)[m]->checkIfAlreadyUse((*damier)[j]))) {
                                            (*monsters)[m]->casesUses.push_back((*damier)[j]);
                                        }

                                        if ((*damier)[j]->isPath && i != j && (!(*monsters)[m]->checkIfAlreadyUse((*damier)[j]))) {
                                            if ((*damier)[j]->coordX == (*damier)[i]->coordX + 1 &&
                                                (*damier)[j]->coordY == (*damier)[i]->coordY &&
                                                (*monsters)[m]->oldDirection != 'L') {

                                                (*monsters)[m]->casesUses.push_back((*damier)[j]);
                                                (*monsters)[m]->oldDirection = 'R';
                                                direction = 'R';
                                            } else if ((*damier)[j]->coordX == (*damier)[i]->coordX &&
                                                       (*damier)[j]->coordY == (*damier)[i]->coordY + 1 &&
                                                       (*monsters)[m]->oldDirection != 'B') {

                                                (*monsters)[m]->casesUses.push_back((*damier)[j]);
                                                (*monsters)[m]->oldDirection = 'T';
                                                direction = 'T';
                                            } else if ((*damier)[j]->coordX == (*damier)[i]->coordX - 1 &&
                                                       (*damier)[j]->coordY == (*damier)[i]->coordY &&
                                                       (*monsters)[m]->oldDirection != 'R') {

                                                (*monsters)[m]->casesUses.push_back((*damier)[j]);
                                                (*monsters)[m]->oldDirection = 'L';
                                                direction = 'L';
                                            } else if ((*damier)[j]->coordX == (*damier)[i]->coordX &&
                                                       (*damier)[j]->coordY == (*damier)[i]->coordY - 1 &&
                                                       (*monsters)[m]->oldDirection != 'T') {

                                                (*monsters)[m]->casesUses.push_back((*damier)[j]);
                                                (*monsters)[m]->oldDirection = 'B';
                                                direction = 'B';
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        (*monsters)[m]->tick(direction);
                    }
                } else if (!game->waitStart) {
                    game->level++;
                    game->credits += (15 * game->level / 5);
                    game->waitStart = true;
                }
            }
        } else {
            for (int i = 0; i < damier->size(); i++) {
                // Si c'est la premiere case du chemin
                if (game->nbMyPath == 0) {
                    if ((*damier)[i]->coordX == 0 || (*damier)[i]->coordX == (game->nbCases-1) || (*damier)[i]->coordY == 0 || (*damier)[i]->coordY == (game->nbCases-1)) {
                        (*damier)[i]->setRGB(0.945f, 0.769f, 0.059f);
                    } else {
                        if (!(*damier)[i]->isPath) {
                            (*damier)[i]->setRGB(0.106f, 0.282f, 0.282f);
                        }
                    }
                } else {
                    if (game->nbMyPath == 1) {
                        if ((game->currentCaseMyPath->coordX == (*damier)[i]->coordX + 1 && game->currentCaseMyPath->coordY == (*damier)[i]->coordY) ||
                            (game->currentCaseMyPath->coordX == (*damier)[i]->coordX     && game->currentCaseMyPath->coordY == (*damier)[i]->coordY + 1) ||
                            (game->currentCaseMyPath->coordX == (*damier)[i]->coordX - 1 && game->currentCaseMyPath->coordY == (*damier)[i]->coordY) ||
                            (game->currentCaseMyPath->coordX == (*damier)[i]->coordX     && game->currentCaseMyPath->coordY == (*damier)[i]->coordY - 1)) {

                            (*damier)[i]->setRGB(0.945f, 0.769f, 0.059f);
                        } else {
                            if (!(*damier)[i]->isPath) {
                                (*damier)[i]->setRGB(0.106f, 0.282f, 0.282f);
                            }
                        }
                    } else {
                        if (((game->currentCaseMyPath->coordX == (*damier)[i]->coordX + 1 && game->currentCaseMyPath->coordY == (*damier)[i]->coordY) ||
                            (game->currentCaseMyPath->coordX == (*damier)[i]->coordX     && game->currentCaseMyPath->coordY == (*damier)[i]->coordY + 1) ||
                            (game->currentCaseMyPath->coordX == (*damier)[i]->coordX - 1 && game->currentCaseMyPath->coordY == (*damier)[i]->coordY) ||
                            (game->currentCaseMyPath->coordX == (*damier)[i]->coordX     && game->currentCaseMyPath->coordY == (*damier)[i]->coordY - 1)) &&
                            (*damier)[i] != game->oldCaseMyPath) {

                            (*damier)[i]->setRGB(0.945f, 0.769f, 0.059f);
                        } else {
                            if (!(*damier)[i]->isPath) {
                                (*damier)[i]->setRGB(0.106f, 0.282f, 0.282f);
                            }
                        }
                    }
                }
            }
        }
    }
}