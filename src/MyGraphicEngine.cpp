//
//  MyGraphicEngine.cpp
//  
//
//  Created by Jérémy Froment on 29/09/2016.
//
//

#include "MyGraphicEngine.h"

/**
 * Function for draw all
 */
void MyGraphicEngine::Draw() {
    if (game->started) {
        GraphicPrimitives::drawFillRect2D(-1.0f, -1.0f, 2.0f, 2.0f, 0.004f, 0.086f, 0.075f);

        for (int i = 0; i < damier->size(); i++) {
            (*damier)[i]->draw();
        }

        for (int i = 0; i < towers->size(); i++) {
            if ((*towers)[i]->alive) {
                (*towers)[i]->draw();
            } else {
                for (int j = 0; j < damier->size(); j++) {
                    if ((*damier)[j]->posX == (*towers)[i]->posX && (*damier)[j]->posY == (*towers)[i]->posY) {
                        (*damier)[j]->haveTower = false;
                        (*damier)[j]->tower     = NULL;
                    }
                }
                towers->erase(towers->begin() + i);
            }
        }

        for (int i = 0; i < monsters->size(); i++) {
            if ((*monsters)[i]->alive) {
                (*monsters)[i]->draw();
            } else {
                game->credits += 20;
                monsters->erase(monsters->begin() + i);
            }
        }

        for (int i = 0; i < shoots->size(); i++) {
            if ((*shoots)[i]->alive) {
                (*shoots)[i]->draw();
                (*shoots)[i]->alive = false;
            } else {
                shoots->erase(shoots->begin() + i);
            }
        }
    }

    game->draw();
}

/**
 * Call on reshape
 *
 * @param width
 * @param height
 */
void MyGraphicEngine::reshape(int width, int height) {
    game->width  = width;
    game->height = height;
}
