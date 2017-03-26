//
// Created by Jérémy Froment on 29/09/2016.
//

#include <GraphicPrimitives.h>
#include "Case.h"

/**
 * Draw case
 */
void Case::draw() {
//    char* coord = new char[6];
//    sprintf(coord, "%d/%d", coordX, coordY);
    GraphicPrimitives::drawFillRect2D(posX, posY, width, height, r, g, b, (isBegin || isEnd) ? 0.5f : 1.0f);
    GraphicPrimitives::drawOutlinedRect2D(posX, posY, width, height, 0.255f, 0.49f, 0.533f);
//    GraphicPrimitives::drawText2D(coord, posX, posY, 0.0f, 0.0f, 0.0f);
}

/**
 * Tick case
 */
void Case::tick() {
    // code trick
}

/**
 * Set RGB color
 *
 * @param r_
 * @param g_
 * @param b_
 */
void Case::setRGB(float r_, float g_, float b_) {
    r = r_;
    g = g_;
    b = b_;
}

/**
 * Return posX
 *
 * @return
 */
float Case::getPosX() {
    return posX;
}

/**
 * Return posY
 *
 * @return
 */
float Case::getPosY() {
    return posY;
}

/**
 * Return if click touch case
 *
 * @param x
 * @param y
 * @return
 */
bool Case::touch(float x, float y) {
    return ((posX <= x && x <= posX + width) && (posY <= y && y <= posY + height) && !isPath);
}

/**
 * Destructor
 */
Case::~Case() {}
