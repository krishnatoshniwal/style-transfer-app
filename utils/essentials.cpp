//
// Created by krishna on 4/2/18.
//

#include "essentials.h"

ResizeBitmap bitmapResizer;

//template<class T>
//void print(const T &any) { std::cout << any << "\n"; }

bool GetBmpFromLocation(std::string p, SimpleBitmap &bmp) {
    /**
     * Fetches an image stored in the path p and returns the image as a bmp object
     */
    FILE *fp = fopen(p.c_str(), "r");
    if (!bmp.LoadPng(fp)) {
        std::cout << "Error:Failed to read the .png file:" << p << std::endl;
        return false;
    } else {
        print(std::string("Loaded " + p));
    }
    return true;
}



//class windowSize()


bool CheckForWindowChange() {
    static double width, height;
    double curWidth = GetCurrentWidth(1.0), curHeight = GetCurrentHeight(1.0);
    if (width == 0 || height == 0) {
        width = curWidth;
        height = curHeight;
    } else if (curHeight != height || curWidth != width) {
        height = curHeight;
        width = curWidth;
        return true;
    }
    return false;
}

namespace windowSize {
    int height = 800, width = 1200;

    void SetWidHei(int wid, int hei) {
        height = hei;
        width = wid;
    }

    int GetWidth() { return width; };

    int GetHeight() { return height; };
}

double GetCurrentHeight(double heightRatio) {
    return heightRatio * windowSize::GetHeight();
}

double GetCurrentWidth(double widthRatio) {
    return widthRatio * windowSize::GetWidth();
}

bool fileExists(std::string name) {
    std::ifstream outputExists(name.c_str());
    return outputExists.good();
}

template <class T>
std::string num2str(T num){
    std::ostringstream ss;
    ss << num;
    return ss.str();
}