//
// Created by Jérémy Froment on 24/10/2016.
//

#include <GraphicPrimitives.h>
#include "TowerRed.h"
#include "TowerGreen.h"
#include "TowerBlue.h"

/**
 * Destructor
 */
Game::~Game() {}

/**
 * Draw general information for game
 */
void Game::draw() {
    if (started) {
        if (!mypath) {
            // Level courant
            char *levelG = new char[8];
            sprintf(levelG, "LEVEL %d", level);
            GraphicPrimitives::drawText2D(levelG, -0.85f, 0.87f, 1.5f, 1.5f, 1.5f);

            // Vie restante
            char *vieG = new char[6];
            sprintf(vieG, "%d", vie);
            GraphicPrimitives::drawFillRect2D(-0.38f, 0.85f, 0.07f, 0.07f, 0.05f, 0.45f, 0.85f);
            GraphicPrimitives::drawText2D(new char[2]{'V', '\0'}, -0.36f, 0.865f, 0.0f, 0.0f, 0.0f);
            GraphicPrimitives::drawText2D(vieG, -0.28f, 0.87f, 1.5f, 1.5f, 1.5f);

            // Credits restants
            char *creditsG = new char[9];
            sprintf(creditsG, "%d$", credits);
            GraphicPrimitives::drawFillRect2D(0.12f, 0.85f, 0.07f, 0.07f, 0.945f, 0.769f, 0.059f);
            GraphicPrimitives::drawText2D(new char[2]{'C', '\0'}, 0.1355f, 0.865f, 0.0f, 0.0f, 0.0f);
            GraphicPrimitives::drawText2D(creditsG, 0.22f, 0.87f, 1.5f, 1.5f, 1.5f);

            // Choix de la tour
            GraphicPrimitives::drawText2D(new char[7]{'T', 'O', 'W', 'E', 'R', 'S', '\0'}, 0.68f, 0.68f, 1.5f, 1.5f,
                                          1.5f);
            GraphicPrimitives::drawFillRect2D(0.68f, 0.55f, 0.05f, 0.05f, 0.90588f, 0.29804f, 0.23529f, (selectedTower == 'R') ? 1.0f : 0.5f); // RED
            GraphicPrimitives::drawFillRect2D(0.75f, 0.55f, 0.05f, 0.05f, 0.161f, 0.992f, 0.184f, (selectedTower == 'G') ? 1.0f : 0.5f); // GREEN
            GraphicPrimitives::drawFillRect2D(0.82f, 0.55f, 0.05f, 0.05f, 0.247f, 0.804f, 0.992f, (selectedTower == 'B') ? 1.0f : 0.5f); // BLUE

            // Si pas de tower selectionné, on selectionne par defaut la tower rouge
            if (currentTower == NULL) {
                currentTower = (TowerAbstract *) new TowerRed(this, 0.0f, 0.0f);
            }

            // On affiche les informations de la tour selectionnée
            GraphicPrimitives::drawText2D(new char[6]{'T', 'O', 'W', 'E', 'R', '\0'}, 0.68f, 0.4f, 1.5f, 1.5f, 1.5f);

            // TYPE
            GraphicPrimitives::drawText2D(new char[7]{'T', 'y', 'p', 'e', ' ', ':', '\0'}, 0.6f, 0.3f, 1.5f, 1.5f, 1.5f);
            GraphicPrimitives::drawFillRect2D(0.75f, 0.29f, 0.05f, 0.05f, currentTower->r, currentTower->g, currentTower->b); // RED

            // LEVEL
            char *levelCT = new char[20];
            sprintf(levelCT, "Level : %d", currentTower->level);
            GraphicPrimitives::drawText2D(levelCT, 0.6f, 0.23f, 1.5f, 1.5f, 1.5f);

            // PRICE
            char *priceCT = new char[20];
            sprintf(priceCT, "Price : %d$", towerPrice(currentTower->getType()) * currentTower->level);
            GraphicPrimitives::drawText2D(priceCT, 0.6f, 0.16f, 1.5f, 1.5f, 1.5f);

            // DAMAGE
            char *damageCT = new char[20];
            sprintf(damageCT, "Dmg : %d", currentTower->puissance * currentTower->level);
            GraphicPrimitives::drawText2D(damageCT, 0.6f, 0.09f, 1.5f, 1.5f, 1.5f);

            // RATE
            char *rateCT = new char[30];
            sprintf(rateCT, "Rate : 1s/%dt", currentTower->frequence);
            GraphicPrimitives::drawText2D(rateCT, 0.6f, 0.02f, 1.5f, 1.5f, 1.5f);

            // RANGE
            char *rangeCT = new char[20];
            sprintf(rangeCT, "Range : %d", currentTower->distanceShoot);
            GraphicPrimitives::drawText2D(rangeCT, 0.6f, -0.05f, 1.5f, 1.5f, 1.5f);

            // Si c'est une tourelle du jeu
            if (currentTower->posX != 0.0f || currentTower->posY != 0.0f) {
                // Bouton upgrade
                char *upgradeCT = new char[20];
                sprintf(upgradeCT, "Upgrade %d$", towerPrice(currentTower->getType()));
                btnUpgrade->setRGBA(0.106f, 0.282f, 0.282f, (credits >= towerPrice(currentTower->getType())) ? 1.0f : 0.5f);
                btnUpgrade->setTxt(upgradeCT);
                btnUpgrade->draw();

                // Bouton sale
                char *saleCT = new char[20];
                sprintf(saleCT, "Sale %d$", towerPrice(currentTower->getType()) * currentTower->level);
                btnSale->setRGBA(0.106f, 0.282f, 0.282f);
                btnSale->setTxt(saleCT);
                btnSale->draw();
            }

            switch (selectedTower) {
                case 'R':
                default:
                    GraphicPrimitives::drawOutlinedRect2D(0.68f, 0.55f, 0.05f, 0.05f, 1.5f, 1.5f, 1.5f); // RED
                    break;
                case 'G':
                    GraphicPrimitives::drawOutlinedRect2D(0.75f, 0.55f, 0.05f, 0.05f, 1.5f, 1.5f, 1.5f); // GREEN
                    break;
                case 'B':
                    GraphicPrimitives::drawOutlinedRect2D(0.82f, 0.55f, 0.05f, 0.05f, 1.5f, 1.5f, 1.5f); // BLUE
                    break;
            }

            if (waitStart) {
                GraphicPrimitives::drawText2D(new char[17]{'P', 'R', 'E', 'S', 'S', ' ', 'g', ' ', 'T', 'O', ' ', 'S', 'T', 'A', 'R', 'T', '\0'}, -0.4f, -0.9f, 1.5f, 1.5f, 1.5f);
            } else {
                if (inPause) {
                    btnResumePause->setRGBA(0.153f, 0.682f, 0.376f);
                    btnResumePause->setMargin(0.08f);
                    btnResumePause->setTxt(new char[7]{'R', 'E', 'S', 'U', 'M', 'E', '\0'});
                } else {
                    btnResumePause->setMargin(0.1f);
                    btnResumePause->setRGBA(0.961f, 0.329f, 0.518f);
                    btnResumePause->setTxt(new char[6]{'P', 'A', 'U', 'S', 'E', '\0'});
                }

                btnResumePause->draw();
            }

            btnRestart->draw();
            btnExit->draw();

            if (gameover) {
                GraphicPrimitives::drawFillRect2D(-0.5f, -0.25f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.8f);
                GraphicPrimitives::drawText2D(new char[23]{'G', 'A', 'M', 'E', ' ', 'O', 'V', 'E', 'R', ' ', '!', '\0'}, -0.19f, 0.1f, 1.5f, 1.5f, 1.5f);
                btnRestartGO->draw();
            }
        } else {
            GraphicPrimitives::drawText2D(new char[15]{'D', 'R', 'A', 'W', ' ', 'Y', 'O', 'U', 'R', ' ', 'P', 'A', 'T', 'H', '\0'}, -0.4f, -0.9f, 1.5f, 1.5f, 1.5f);
            btnValidPath->draw();
        }
    } else {
        GraphicPrimitives::drawText2D(new char[23] {'W', 'E', 'L', 'C', 'O', 'M', 'E', ' ', 'T', 'O', ' ', 'V', 'E', 'C', 'T', 'O', 'R', ' ', 'T', 'D', ' ', '!', '\0'}, -0.25f, 0.8f, 1.5f, 1.5f, 1.5f);

        // Bouton de validation du choix de chemin
        btnStartGame->draw();

        // choisir le chemin
        GraphicPrimitives::drawText2D(new char[12]{'C', 'H', 'O', 'O', 'S', 'E', ' ', 'P', 'A', 'T', 'H', '\0'}, -0.12f, 0.3f, 1.5f, 1.5f, 1.5f);

        // Chemin 1
        GraphicPrimitives::drawFillRect2D(-0.5f, 0.0f, 0.2f, 0.2f, 0.106f, 0.282f, 0.282f, (choosePath == 1) ? 1.0f : 0.5f); // PATH 1
        GraphicPrimitives::drawText2D(new char[7]{'P', 'A', 'T', 'H', ' ', '1', '\0'}, -0.48f, 0.08f, 1.5f, 1.5f, 1.5f, (choosePath == 1) ? 1.0f : 0.5f);

        // Chemin 2
        GraphicPrimitives::drawFillRect2D(-0.2f, 0.0f, 0.2f, 0.2f, 0.106f, 0.282f, 0.282f, (choosePath == 2) ? 1.0f : 0.5f); // PATH 2
        GraphicPrimitives::drawText2D(new char[7]{'P', 'A', 'T', 'H', ' ', '2', '\0'}, -0.18f, 0.08f, 1.5f, 1.5f, 1.5f, (choosePath == 2) ? 1.0f : 0.5f);

        // Chemin 3
        GraphicPrimitives::drawFillRect2D( 0.1f, 0.0f, 0.2f, 0.2f, 0.106f, 0.282f, 0.282f, (choosePath == 3) ? 1.0f : 0.5f); // PATH 3
        GraphicPrimitives::drawText2D(new char[7]{'P', 'A', 'T', 'H', ' ', '3', '\0'}, 0.12f, 0.08f, 1.5f, 1.5f, 1.5f, (choosePath == 3) ? 1.0f : 0.5f);

        // Chemin 4
        GraphicPrimitives::drawFillRect2D( 0.4f, 0.0f, 0.2f, 0.2f, 0.106f, 0.282f, 0.282f, (choosePath == 4) ? 1.0f : 0.5f); // PATH 4
        GraphicPrimitives::drawText2D(new char[7]{'P', 'A', 'T', 'H', ' ', '4', '\0'}, 0.42f, 0.08f, 1.5f, 1.5f, 1.5f, (choosePath == 4) ? 1.0f : 0.5f);

        // Chemin du joueur
        GraphicPrimitives::drawFillRect2D(-0.1f, -0.3f, 0.3f, 0.2f, 0.106f, 0.282f, 0.282f, (choosePath == 0) ? 1.0f : 0.5f); // PATH 4
        GraphicPrimitives::drawText2D(new char[8]{'M', 'Y', ' ', 'P', 'A', 'T', 'H', '\0'}, -0.045f, -0.22f, 1.5f, 1.5f, 1.5f, (choosePath == 0) ? 1.0f : 0.5f);
    }
}

/**
 * Return touch button resume/pause
 *
 * @param x
 * @param y
 * @return
 */
bool Game::touchResumePause(float x, float y) {
    return btnResumePause->touch(x, y);
}

/**
 * Select current tower touched
 *
 * @param x
 * @param y
 */
void Game::touchTower(float x, float y) {
    if ((0.68f < x && x < 0.68f + 0.05f) && (0.55f < y && y < 0.55f + 0.05f)) {
        selectedTower = 'R';
        currentTower = new TowerRed(this, 0.0f, 0.0f);
    } else if ((0.75f < x && x < 0.75f + 0.05f) && (0.55f < y && y < 0.55f + 0.05f)) {
        selectedTower = 'G';
        currentTower = new TowerGreen(this, 0.0f, 0.0f);
    } else if ((0.82f < x && x < 0.82f + 0.05f) && (0.55f < y && y < 0.55f + 0.05f)) {
        selectedTower = 'B';
        currentTower = new TowerBlue(this, 0.0f, 0.0f);
    }
}

void Game::touchPath(float x, float y) {
    if ((-0.5f < x && x < -0.5f + 0.2f) && (0.0f < y && y < 0.0f + 0.2f)) {
        choosePath = 1;
    } else if ((-0.2f < x && x < -0.2f + 0.2f) && (0.0f < y && y < 0.0f + 0.2f)) {
        choosePath = 2;
    } else if ((0.1f < x && x < 0.1f + 0.2f) && (0.0f < y && y < 0.0f + 0.2f)) {
        choosePath = 3;
    } else if ((0.4f < x && x < 0.4f + 0.2f) && (0.0f < y && y < 0.0f + 0.2f)) {
        choosePath = 4;
    } else if ((-0.1f < x && x < -0.1f + 0.3f) && (-0.3f < y && y < -0.3f + 0.2f)) {
        choosePath = 0;
    }
}

/**
 * Return tower price
 *
 * @param tower
 * @return
 */
int Game::towerPrice(char tower) {
    switch (tower) {
        case 'G':
            return priceTowerG;

        case 'B':
            return priceTowerB;

        case 'R':
        default:
            return priceTowerR;
    }
}

/**
 * Return if touch button upgrade
 *
 * @param x
 * @param y
 */
void Game::touchUpgrade(float x, float y) {
    if (btnUpgrade->touch(x, y) && credits >= towerPrice(currentTower->getType())) {
        credits -= towerPrice(currentTower->getType());
        if (currentTower->level <= 9) {
            currentTower->level++;
        }

        if (currentTower->level % 3 == 0 && currentTower->distanceShoot <= 4) {
            currentTower->distanceShoot = currentTower->distanceShoot + 1;
        }
    }
}

/**
 * Return if touch button sale
 *
 * @param x
 * @param y
 */
void Game::touchSale(float x, float y) {
    if (btnSale->touch(x, y)) {
        credits += towerPrice(currentTower->getType()) * currentTower->level;
        currentTower->alive = false;
    }
}

/**
 * Define path
 *
 * return 0 = false
 * return 1 = true (is path)
 * return 2 = true (is path begin)
 * return 3 = true (is path end)
 *
 * @param path
 * @param x
 * @param y
 * @return
 */
int Game::isPath(int path, int x, int y) {
    switch (path) {
        case 0:
            break;

        case 1:
        default:
            if ((x == 0 && y == 4) ||
                (x == 1 && y == 4) ||
                (x == 2 && y == 4) ||
                (x == 3 && y == 4) ||
                (x == 4 && y == 4) ||
                (x == 5 && y == 4) ||
                (x == 5 && y == 5) ||
                (x == 5 && y == 6) ||
                (x == 5 && y == 7) ||
                (x == 6 && y == 7) ||
                (x == 7 && y == 7) ||
                (x == 8 && y == 7) ||
                (x == 9 && y == 7) ||
                (x == 10 && y == 7) ||
                (x == 11 && y == 7)) {

                if (x == 0 && y == 4) {
                    return 2;
                }

                if (x == 11 && y == 7) {
                    return 3;
                }

                return 1;
            }

            break;
        case 2:
            if ((x == 3 && y == 11) ||
                (x == 3 && y == 10) ||
                (x == 4 && y == 10) ||
                (x == 5 && y == 10) ||
                (x == 5 && y == 9) ||
                (x == 6 && y == 9) ||
                (x == 7 && y == 9) ||
                (x == 8 && y == 9) ||
                (x == 9 && y == 9) ||
                (x == 10 && y == 9) ||
                (x == 10 && y == 8) ||
                (x == 10 && y == 7) ||
                (x == 10 && y == 6) ||
                (x == 10 && y == 5) ||
                (x == 10 && y == 4) ||
                (x == 11 && y == 4)) {

                if (x == 3 && y == 11) {
                    return 2;
                }

                if (x == 11 && y == 4) {
                    return 3;
                }

                return 1;
            }

            break;

        case 3:
            if ((x == 4 && y == 0) ||
                (x == 5 && y == 0) ||
                (x == 6 && y == 0) ||
                (x == 7 && y == 0) ||
                (x == 7 && y == 1) ||
                (x == 8 && y == 1) ||
                (x == 8 && y == 2) ||
                (x == 8 && y == 3) ||
                (x == 8 && y == 4) ||
                (x == 8 && y == 5) ||
                (x == 8 && y == 6) ||
                (x == 8 && y == 7) ||
                (x == 8 && y == 8) ||
                (x == 8 && y == 9) ||
                (x == 9 && y == 9) ||
                (x == 10 && y == 9) ||
                (x == 11 && y == 9)) {

                if (x == 4 && y == 0) {
                    return 2;
                }

                if (x == 11 && y == 9) {
                    return 3;
                }

                return 1;
            }

            break;

        case 4:
            if ((x == 0 && y == 10) ||
                (x == 1 && y == 10) ||
                (x == 2 && y == 10) ||
                (x == 3 && y == 10) ||
                (x == 4 && y == 10) ||
                (x == 4 && y == 9) ||
                (x == 4 && y == 8) ||
                (x == 5 && y == 8) ||
                (x == 5 && y == 7) ||
                (x == 6 && y == 7) ||
                (x == 7 && y == 7) ||
                (x == 8 && y == 7) ||
                (x == 9 && y == 7) ||
                (x == 10 && y == 7) ||
                (x == 11 && y == 7)) {

                if (x == 0 && y == 10) {
                    return 2;
                }

                if (x == 11 && y == 7) {
                    return 3;
                }

                return 1;
            }

            break;
    }

    return 0;
}

/**
 * Return if click on start game button
 *
 * @param x
 * @param y
 * @return
 */
bool Game::touchStartGame(float x, float y) {
    return btnStartGame->touch(x, y);
}

/**
 * Return if click on exit button
 *
 * @param x_
 * @param y_
 * @return
 */
bool Game::touchExit(float x_, float y_) {
    return btnExit->touch(x_, y_);
}

/**
 * Return if click on restart button
 *
 * @param x_
 * @param y_
 * @return
 */
bool Game::touchRestart(float x_, float y_) {
    return btnRestart->touch(x_, y_);
}

/**
 * Return if click on restart gameover button
 *
 * @param x_
 * @param y_
 * @return
 */
bool Game::touchRestartGO(float x_, float y_) {
    return btnRestartGO->touch(x_, y_);
}

/**
 * Return if click on create path for path from player
 *
 * @param x_
 * @param y_
 * @return
 */
bool Game::touchValidPath(float x_, float y_) {
    return btnValidPath->touch(x_, y_);
}
