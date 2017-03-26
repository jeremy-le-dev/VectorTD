//
// Created by Jérémy Froment on 25/11/2016.
//

#ifndef VECTORTD_BUTTON_H
#define VECTORTD_BUTTON_H

class Button {
public:
    float posX, posY, width, height, r, g, b, a, marginLeft;
    char* txt;

    Button(char* txt_, float posX_, float posY_, float width_, float height_, float r_, float g_, float b_, float a_ = 1.0f, float marginLeft_ = 0.0f) : txt(txt_), posX(posX_), posY(posY_), width(width_), height(height_), r(r_), g(g_), b(b_), a(a_), marginLeft(marginLeft_) {}

    void draw();

    bool touch(float xParam, float yParam);

    void setRGBA(float r_, float g_, float b_, float a_ = 1.0f);

    void setTxt(char *txt_);

    ~Button();

    void setMargin(float m);
};


#endif //VECTORTD_BUTTON_H