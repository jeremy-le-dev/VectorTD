//
//  MonsterAbstract.cpp
//  
//
//  Created by Jérémy Froment on 05/10/2016.
//
//

#include <vector>
#include <GraphicPrimitives.h>
#include "MonsterAbstract.h"

/**
 * Destructor
 */
MonsterAbstract::~MonsterAbstract() {}

/**
 * Draw monster
 */
void MonsterAbstract::draw() {
    if (posX >= game->leftPos &&
        posX <= game->leftPos + game->gameSize &&
        posY >= -(game->gameSize / 2) &&
        posY <= (game->gameSize / 2)) {

        float x1 = posX + width / 4;
        float x2 = posX + (3 * width) / 8;
        float x3 = posX + (5 * width) / 8;
        float x4 = posX + (3 * width) / 4;
        float x5 = x3;
        float x6 = x2;

        float y1 = posY + height / 2;
        float y2 = posY + (3 * height) / 4;
        float y3 = y2;
        float y4 = y1;
        float y5 = posY + height / 4;
        float y6 = y5;

        std::vector<float> vectX = {x1, x2, x3, x4, x5, x6};
        std::vector<float> vectY = {y1, y2, y3, y4, y5, y6};

        GraphicPrimitives::drawFillPolygone2D(vectX, vectY, r, g, b);
        GraphicPrimitives::drawFillRect2D(posX, posY + height / 20, (vie * width) / vieFull, height / 10, 0.161f, 0.992f, 0.184f);
    }
}

/**
 * Tick monster with direction
 *
 * @param direction
 */
void MonsterAbstract::tick(char direction) {
    if (vitesse < defaultVitesse) {
        if (incrFrequence == 20) {
            vitesse = defaultVitesse;
            incrFrequence = 0;
        } else {
            incrFrequence++;
        }
    }

    if (direction == 'E') {
        game->vie--;
        posX = posXBegin;
        posY = posYBegin;
        casesUses.clear();
        oldDirection = beginDirection;
    } else {
        switch (direction) {
            case 'T':
                posY += vitesse;
                break;

            case 'R':
            default:
                posX += vitesse;
                break;

            case 'B':
                posY -= vitesse;
                break;

            case 'L':
                posX -= vitesse;
                break;
        }
    }
}

/**
 * Return if case in parameter is already use by monster
 *
 * @param case_
 * @return
 */
bool MonsterAbstract::checkIfAlreadyUse(Case *&case_) {
    for (int i = 0; i < casesUses.size(); i++) {
        if (casesUses[i] == case_) {
            return true;
        }
    }

    return false;
}