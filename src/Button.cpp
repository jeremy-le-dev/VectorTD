//
// Created by Jérémy Froment on 25/11/2016.
//
#include <GraphicPrimitives.h>
#include "Button.h"

/**
 * Draw button
 */
void Button::draw() {
    GraphicPrimitives::drawFillRect2D(posX, posY, width, height, r, g, b, a);
    GraphicPrimitives::drawText2D(txt, posX + ((marginLeft != 0.0f) ? marginLeft : (width / 5)), posY + (height / 3), 1.5f, 1.5f, 1.5f, a);
}

/**
 * Return if click on button
 *
 * @param xParam
 * @param yParam
 * @return
 */
bool Button::touch(float xParam, float yParam) {
    return ((posX < xParam && xParam < posX + width) && (posY < yParam && yParam < posY + height));
}

/**
 * Set RGBA color
 *
 * @param r_
 * @param g_
 * @param b_
 * @param a_
 */
void Button::setRGBA(float r_, float g_, float b_, float a_) {
    r = r_;
    g = g_;
    b = b_;
    a = a_;
}

/**
 * Set text in button
 *
 * @param txt_
 */
void Button::setTxt(char *txt_) {
    txt = txt_;
}

/**
 * Destructor
 */
Button::~Button() {}

/**
 * Set margin left for text in button
 *
 * @param m
 */
void Button::setMargin(float m) {
    marginLeft = m;
}
