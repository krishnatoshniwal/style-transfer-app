#include "button.h"

Button::Button(std::string incoming, int given_x, int given_y, int width, int height, bool (*fP)(void)) {
    Set(incoming, given_x, given_y, width, height, fP);
}

Button::~Button() {
    CleanUp();
}


void Button::Set(std::string incoming, int given_x, int given_y, int width, int height, bool (*functocall)(void)) {
    x = given_x;
    y = given_y;
    wid = width;
    hei = height;

    name = incoming;
}

void Button::Set(std::string incoming, ImageLocations imgLocs, bool (*functocall)(void)) {
    name = incoming;

    x = imgLocs.x + imgLocs.imWidth / 2 - wid / 2;
    y = imgLocs.y + 2 + hei;

    fP = functocall;
}

void Button::CleanUp(void) {}

int Button::CheckButton(int mx, int my) {
    mouseOnButton = false;
    if (mx > x && mx < x + wid && my > y - hei && my < y) {
        mouseOnButton = true;
        return 1;
    }
    return 0;
}

void Button::Draw(void) {
    glColor3ub(0, 0, 0);
    if (mouseOnButton) {
        glColor3ub(255, 0, 0);
    }

    glBegin(GL_LINE_LOOP);
    glVertex2i(x, y + 2);
    glVertex2i(x + wid, y + 2);
    glVertex2i(x + wid, y - hei + 2);
    glVertex2i(x, y - hei + 2);
    glEnd();

    int strLen = name.length();
    int xFont = x + wid / 2 - 13 * (strLen / 2), yFont = y - 1;
    glRasterPos2i(xFont, yFont);
    YsGlDrawFontBitmap12x16(name.c_str());
    glColor3ub(0, 0, 0);

}


bool (*execB1)(void) = &B1Action;

bool (*execB2)(void) = &B2Action;

bool (*execB3)(void) = &B3Action;

bool (*execB4)(void) = &B4Action;

void ButtonUI::Initialise() {
    buttons.resize(4);
    Button b1, b2, b3, b4;

    b1.Set("Update", ImgSet::AllStylesImageLocs(), execB1);
    b2.Set("Update", ImgSet::GetContentImageLocs(), execB2);
    b3.Set("G0!", ImgSet::GetStyleImageLocs(), execB3);
    b4.Set("All In!", ImgSet::GetOutputImageLocs(), execB4);

    buttons[0] = b1;
    buttons[1] = b2;
    buttons[2] = b3;
    buttons[3] = b4;

    isAllIn = false;

}

void ButtonUI::Draw() {
    for (auto &bt:buttons) {
        if (!isAllIn)
            bt.Draw();
    }
}

bool ButtonUI::Interval(int mx, int my, bool clicked) {
    bool needRedraw = true;
    int i = 0;
    for (auto &bt:buttons) {
        if (bt.CheckButton(mx, my) == 1) {
            needRedraw = true;
            if (clicked && !isAllIn) {
                if (i == 3) {
                    isAllIn = true;
                }
                bt.fP();
                isAllIn = false;
            }
        };
        i++;
    }
    return needRedraw;
}