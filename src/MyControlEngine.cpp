//
// Created by Jérémy Froment on 29/09/2016.
//

#include <thread>
#include "MyControlEngine.h"
#include "TowerRed.h"
#include "TowerGreen.h"
#include "TowerBlue.h"
#include "MonsterRed.h"
#include "MonsterGreen.h"
#include "MonsterPurple.h"
#include "MonsterYellow.h"

/**
 * Callback on mouse click
 *
 * @param button
 * @param state
 * @param x
 * @param y
 */
void MyControlEngine::MouseCallback(int button, int state, int x, int y) {
    float x_ = (float)(x - (game->width/2)) / (game->width/2);
    float y_ = (float)(y - (game->height/2)) / - (game->height/2);

    // Clique gauche de la souris
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (game->started && !game->gameover) {
            if (!game->mypath) {
                // on reset tout le game pour revenir à l'état de départ
                if (game->touchExit(x_, y_)) {
                    game->credits = 200;
                    game->points = 0;
                    game->vie = 20;
                    game->level = 1;
                    game->waitStart = true;
                    game->started = false;
                    game->inPause = false;
                    game->selectedTower = 'R';

                    damier->clear();
                    towers->clear();
                    monsters->clear();
                    shoots->clear();
                }

                // on reset la partie en cours pour la recommencer
                if (game->touchRestart(x_, y_)) {
                    game->credits = 200;
                    game->points = 0;
                    game->vie = 20;
                    game->level = 1;
                    game->waitStart = true;
                    game->inPause = false;
                    game->selectedTower = 'R';

                    towers->clear();
                    monsters->clear();
                    shoots->clear();
                }

                // On boucle sur les cases du damier
                for (int i = 0; i < damier->size(); i++) {
                    // Si on clique sur une case du damier
                    if ((*damier)[i]->touch(x_, y_)) {
                        // Si la case n'a pas de tour
                        if (!(*damier)[i]->haveTower) {
                            if (game->credits >= game->towerPrice(game->selectedTower)) {
                                game->credits -= game->towerPrice(game->selectedTower);
                                (*damier)[i]->haveTower = true;

                                switch (game->selectedTower) {
                                    case 'R':
                                    default:
                                        towers->push_back((TowerAbstract *) new TowerRed(game, (*damier)[i]->getPosX(),
                                                                                         (*damier)[i]->getPosY()));
                                        break;
                                    case 'G':
                                        towers->push_back(
                                                (TowerAbstract *) new TowerGreen(game, (*damier)[i]->getPosX(),
                                                                                 (*damier)[i]->getPosY()));
                                        break;
                                    case 'B':
                                        towers->push_back((TowerAbstract *) new TowerBlue(game, (*damier)[i]->getPosX(),
                                                                                          (*damier)[i]->getPosY()));
                                        break;
                                }

                                game->currentTower = (TowerAbstract *) (*towers)[towers->size() - 1];
                                (*damier)[i]->tower = (TowerAbstract *) (*towers)[towers->size() - 1];
                            }
                        } else {
                            game->currentTower = (*damier)[i]->tower;
                        }
                    }
                }

                // Seulement si le jeu est commencé
                if (!game->waitStart) {
                    if (game->touchResumePause(x_, y_)) {
                        game->inPause = !game->inPause;
                    }
                }

                // Si c'est une tourelle du jeu (pas une tourelle à acheter)
                if (game->currentTower->posX != 0.0f || game->currentTower->posY != 0.0f) {
                    // Si j'ai assez de credits, je peux upgrader la tourelle
                    if (game->credits >= game->towerPrice(game->currentTower->getType())) {
                        game->touchUpgrade(x_, y_);
                    }
                    game->touchSale(x_, y_);
                }

                game->touchTower(x_, y_);
            } else {
                if (game->touchValidPath(x_, y_) && game->nbMyPath > 2) {
                    game->endXPath = game->currentCaseMyPath->posX;
                    game->endYPath = game->currentCaseMyPath->posY;
                    game->currentCaseMyPath->isEnd = true;
                    game->currentCaseMyPath->setRGB(0.906f, 0.298f, 0.235f);

                    for (int i = 0; i < damier->size(); i++) {
                        if (((game->currentCaseMyPath->coordX == (*damier)[i]->coordX + 1 && game->currentCaseMyPath->coordY == (*damier)[i]->coordY) ||
                             (game->currentCaseMyPath->coordX == (*damier)[i]->coordX     && game->currentCaseMyPath->coordY == (*damier)[i]->coordY + 1) ||
                             (game->currentCaseMyPath->coordX == (*damier)[i]->coordX - 1 && game->currentCaseMyPath->coordY == (*damier)[i]->coordY) ||
                             (game->currentCaseMyPath->coordX == (*damier)[i]->coordX     && game->currentCaseMyPath->coordY == (*damier)[i]->coordY - 1)) &&
                             (*damier)[i] != game->oldCaseMyPath) {

                            (*damier)[i]->setRGB(0.106f, 0.282f, 0.282f);
                        }
                    }

                    game->mypath = false;
                    game->nbMyPath = 0;
                    game->currentCaseMyPath = NULL;
                    game->oldCaseMyPath = NULL;
                } else {
                    // On boucle sur les cases du damier
                    for (int i = 0; i < damier->size(); i++) {
                        // Si on clique sur une case du damier
                        if ((*damier)[i]->touch(x_, y_)) {
                            // Si c'est la premiere case (depart)
                            if (game->nbMyPath == 0) {
                                if ((*damier)[i]->coordX == 0 || (*damier)[i]->coordX == (game->nbCases - 1) ||
                                    (*damier)[i]->coordY == 0 || (*damier)[i]->coordY == (game->nbCases - 1)) {

                                    (*damier)[i]->isBegin = true;
                                    (*damier)[i]->isPath = true;
                                    (*damier)[i]->setRGB(0.18f, 0.8f, 0.443f);
                                    game->currentCaseMyPath = (*damier)[i];
                                    game->nbMyPath++;
                                    game->beginXPath = (*damier)[i]->posX;
                                    game->beginYPath = (*damier)[i]->posY;
                                }
                            } else {
                                if (game->nbMyPath == 1) {
                                    if ((game->currentCaseMyPath->coordX == (*damier)[i]->coordX + 1 &&
                                         game->currentCaseMyPath->coordY == (*damier)[i]->coordY) ||
                                        (game->currentCaseMyPath->coordX == (*damier)[i]->coordX &&
                                         game->currentCaseMyPath->coordY == (*damier)[i]->coordY + 1) ||
                                        (game->currentCaseMyPath->coordX == (*damier)[i]->coordX - 1 &&
                                         game->currentCaseMyPath->coordY == (*damier)[i]->coordY) ||
                                        (game->currentCaseMyPath->coordX == (*damier)[i]->coordX &&
                                         game->currentCaseMyPath->coordY == (*damier)[i]->coordY - 1)) {

                                        (*damier)[i]->isPath = true;
                                        (*damier)[i]->setRGB(0.008f, 0.18f, 0.157f);
                                        game->oldCaseMyPath = game->currentCaseMyPath;
                                        game->currentCaseMyPath = (*damier)[i];
                                        game->nbMyPath++;
                                    }
                                } else {
                                    if (((game->currentCaseMyPath->coordX == (*damier)[i]->coordX + 1 &&
                                          game->currentCaseMyPath->coordY == (*damier)[i]->coordY) ||
                                         (game->currentCaseMyPath->coordX == (*damier)[i]->coordX &&
                                          game->currentCaseMyPath->coordY == (*damier)[i]->coordY + 1) ||
                                         (game->currentCaseMyPath->coordX == (*damier)[i]->coordX - 1 &&
                                          game->currentCaseMyPath->coordY == (*damier)[i]->coordY) ||
                                         (game->currentCaseMyPath->coordX == (*damier)[i]->coordX &&
                                          game->currentCaseMyPath->coordY == (*damier)[i]->coordY - 1)) &&
                                         (*damier)[i] != game->oldCaseMyPath) {

                                        (*damier)[i]->isPath = true;
                                        (*damier)[i]->setRGB(0.008f, 0.18f, 0.157f);
                                        game->oldCaseMyPath = game->currentCaseMyPath;
                                        game->currentCaseMyPath = (*damier)[i];
                                        game->nbMyPath++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if (game->gameover) {
                if (game->touchRestartGO(x_, y_)) {
                    game->credits         = 200;
                    game->points          = 0;
                    game->vie             = 20;
                    game->level           = 1;
                    game->waitStart       = true;
                    game->started         = false;
                    game->inPause         = false;
                    game->selectedTower   = 'R';
                    game->gameover        = false;

                    damier->clear();
                    towers->clear();
                    monsters->clear();
                    shoots->clear();
                }
            } else {
                game->touchPath(x_, y_);

                if (game->touchStartGame(x_, y_)) {
                    int x = 0;
                    for (float r = game->leftPos; r < (game->leftPos + game->gameSize); r += game->pas) {
                        int y = 0;
                        for (float c = -(game->gameSize / 2); c < game->gameSize / 2; c += game->pas) {
                            Case *cas = new Case(game, r, c);
                            cas->coordX = x;
                            cas->coordY = y;

                            // Si ce n'est pas le chemin du joueur
                            if (game->choosePath > 0) {
                                // Si la case fait partie du chemin
                                if (game->isPath(game->choosePath, x, y) != 0) {
                                    cas->isPath = true;
                                    cas->setRGB(0.008f, 0.18f, 0.157f);

                                    // Si c'est la case de départ
                                    if (game->isPath(game->choosePath, x, y) == 2) {
                                        game->beginXPath = r;
                                        game->beginYPath = c;
                                        cas->isBegin = true;
                                        cas->setRGB(0.18f, 0.8f, 0.443f);
                                    }

                                    // Si c'est la case de fin
                                    if (game->isPath(game->choosePath, x, y) == 3) {
                                        game->endXPath = r;
                                        game->endYPath = c;
                                        cas->isEnd = true;
                                        cas->setRGB(0.906f, 0.298f, 0.235f);
                                    }
                                }
                            }

                            damier->push_back(cas);
                            y++;
                        }
                        x++;
                    }
                    game->started = true;

                    if (game->choosePath == 0) {
                        game->mypath = true;
                    }
                }
            }
        }
    }
}

/**
 * Callback on keypress
 *
 * @param key
 * @param x
 * @param y
 */
void MyControlEngine::KeyboardCallback(unsigned char key, int x, int y) {
    std::vector<MonsterAbstract *> listMonsters;

    if (game->started) {
        if (game->waitStart) {
            switch (key) {
                case 'g':
                    // Initialisation des variables
                    game->waitStart = false;
                    game->credits += (15 * game->level/5);

                    // On determine le type de monstre qui va être envoyé dans cette vague avec son level par rapport au
                    // level de la partie
                    switch (game->level%5) {
                        case 0:
                        default:
                            listMonsters.push_back((MonsterAbstract*) new MonsterRed(game, game->beginXPath, game->beginYPath));
                            listMonsters.push_back((MonsterAbstract*) new MonsterRed(game, game->beginXPath, game->beginYPath));
                            listMonsters.push_back((MonsterAbstract*) new MonsterRed(game, game->beginXPath, game->beginYPath));
                            listMonsters.push_back((MonsterAbstract*) new MonsterRed(game, game->beginXPath, game->beginYPath));
                            createMonsterWithInterval(listMonsters);
                            break;

                        case 1:
                            listMonsters.push_back((MonsterAbstract*) new MonsterGreen(game, game->beginXPath, game->beginYPath));
                            listMonsters.push_back((MonsterAbstract*) new MonsterGreen(game, game->beginXPath, game->beginYPath));
                            listMonsters.push_back((MonsterAbstract*) new MonsterGreen(game, game->beginXPath, game->beginYPath));
                            listMonsters.push_back((MonsterAbstract*) new MonsterGreen(game, game->beginXPath, game->beginYPath));
                            createMonsterWithInterval(listMonsters);
                            break;

                        case 2:
                            listMonsters.push_back((MonsterAbstract*) new MonsterPurple(game, game->beginXPath, game->beginYPath));
                            listMonsters.push_back((MonsterAbstract*) new MonsterPurple(game, game->beginXPath, game->beginYPath));
                            listMonsters.push_back((MonsterAbstract*) new MonsterPurple(game, game->beginXPath, game->beginYPath));
                            listMonsters.push_back((MonsterAbstract*) new MonsterPurple(game, game->beginXPath, game->beginYPath));
                            createMonsterWithInterval(listMonsters);
                            break;

                        case 3:
                            listMonsters.push_back((MonsterAbstract*) new MonsterYellow(game, game->beginXPath, game->beginYPath));
                            listMonsters.push_back((MonsterAbstract*) new MonsterYellow(game, game->beginXPath, game->beginYPath));
                            listMonsters.push_back((MonsterAbstract*) new MonsterYellow(game, game->beginXPath, game->beginYPath));
                            listMonsters.push_back((MonsterAbstract*) new MonsterYellow(game, game->beginXPath, game->beginYPath));
                            createMonsterWithInterval(listMonsters);
                            break;

                        case 4:
                            listMonsters.push_back((MonsterAbstract*) new MonsterRed(game, game->beginXPath, game->beginYPath));
                            listMonsters.push_back((MonsterAbstract*) new MonsterGreen(game, game->beginXPath, game->beginYPath));
                            listMonsters.push_back((MonsterAbstract*) new MonsterPurple(game, game->beginXPath, game->beginYPath));
                            listMonsters.push_back((MonsterAbstract*) new MonsterYellow(game, game->beginXPath, game->beginYPath));
                            createMonsterWithInterval(listMonsters);
                            break;
                    }

                    break;

                default:
                    break;
            }
        }
    }
}

/**
 * Function for create monster with interval
 *
 * @param listMonsters
 */
void MyControlEngine::createMonsterWithInterval(std::vector<MonsterAbstract *> &listMonsters) {
    int i = 0;
    while (i < listMonsters.size()) {
        if (game->beginXPath == game->leftPos) { // gauche
            listMonsters[i]->posX -= (game->pas * i);
            listMonsters[i]->oldDirection = 'R';
            listMonsters[i]->beginDirection = 'R';
        } else if (game->beginXPath == game->leftPos + game->gameSize - game->pas) { // droite
            listMonsters[i]->posX += (game->pas * i);
            listMonsters[i]->oldDirection = 'L';
            listMonsters[i]->beginDirection = 'L';
        } else if (game->beginYPath == game->gameSize / 2 - game->pas) { // haut
            listMonsters[i]->posY += (game->pas * i);
            listMonsters[i]->oldDirection = 'B';
            listMonsters[i]->beginDirection = 'B';
        } else if (game->beginYPath == -(game->gameSize / 2)) { // bas
            listMonsters[i]->posY -= (game->pas * i);
            listMonsters[i]->oldDirection = 'T';
            listMonsters[i]->beginDirection = 'T';
        }

        monsters->push_back(listMonsters[i]);
        i++;
    }
}
