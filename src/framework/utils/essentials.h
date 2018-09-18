//
// Created by krishna on 4/2/18.
//

#ifndef PROJECT_ESSENTIALS_H
#define PROJECT_ESSENTIALS_H

#include "libraries.h"

extern ResizeBitmap bitmapResizer;

// Essential Classes and Functions
using std::vector;

template<class T>
inline void print(const T &any) { std::cout << any << "\n"; }

bool GetBmpFromLocation(std::string p, SimpleBitmap &bmp);

namespace windowSize {
    extern int height, width;

    void SetWidHei(int wid, int hei);

    int GetWidth();

    int GetHeight();
}

double GetCurrentHeight(double heightRatio);

double GetCurrentWidth(double widthRatio);

class Event {
public:
    int key, mx, my;
    bool clicked;

    Event(int key, int mx, int my, bool clicked) {
        this->key = key;
        this->mx = mx;
        this->my = my;
        this->clicked = clicked;
    }

    void GetEvent(int &key, int &mx, int &my, bool &clicked) {
        key = this->key;
        mx = this->mx;
        my = this->my;
        clicked = this->clicked;
    }
};

bool CheckForWindowChange();

bool fileExists(std::string name);

template <class T>
std::string num2str(T num);

#endif //PROJECT_ESSENTIALS_H
