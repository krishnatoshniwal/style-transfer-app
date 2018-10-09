#ifndef PROJECT_RESIZEBMP_H
#define PROJECT_RESIZEBMP_H


#include "libraries.h"

class ResizeBitmap{
private:
    cimg_library::CImg<unsigned char> ConvertToCImg(SimpleBitmap bmp);
    SimpleBitmap ConvertToBMP(cimg_library::CImg<unsigned char> img);
public:
    void ResizeBmp(SimpleBitmap bmp,SimpleBitmap &resized_bmp, int wid,int hei);
};


#endif 
