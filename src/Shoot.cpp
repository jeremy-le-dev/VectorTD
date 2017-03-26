//
//  Shoot.cpp
//  
//
//  Created by Jérémy Froment on 06/10/2016.
//
//

#include <GraphicPrimitives.h>
#include "Shoot.h"

/**
 * Draw shoot
 */
void Shoot::draw() {
    GraphicPrimitives::drawLine2D(posX1 + (game->pas / 2), posY1 + (game->pas / 2), posX2 + (game->pas / 2), posY2 + (game->pas / 2), r, g, b);

    for (float i = 0.001f; i < 0.005f; i += 0.001f) {
        GraphicPrimitives::drawLine2D(posX1 + (game->pas / 2) + i, posY1 + (game->pas / 2) + i, posX2 + (game->pas / 2) + i, posY2 + (game->pas / 2) + i, r, g, b);
        GraphicPrimitives::drawLine2D(posX1 + (game->pas / 2) - i, posY1 + (game->pas / 2) - i, posX2 + (game->pas / 2) - i, posY2 + (game->pas / 2) - i, r, g, b);
    }
}

/**
 * Destructor
 */
Shoot::~Shoot() {}
