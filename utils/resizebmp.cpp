#include "resizebmp.h"

cimg_library::CImg<unsigned char> ResizeBitmap::ConvertToCImg(SimpleBitmap bmp) {
    auto bmpPtr = bmp.GetBitmapPointer();
    auto wid = bmp.GetWidth();
    auto hei = bmp.GetHeight();
    auto totalNum = wid * hei;
    cimg_library::CImg<unsigned char> destImg(wid, hei, 1, 3);

    for (int i = 0; i < wid; i++) {
        for (int j = 0; j < hei; j++) {
            for (int c = 0; c < 3; c++) {
                switch (c) {
                    case 0:
                        destImg(i, j, c) = bmpPtr[4 * (wid * j + i) + 0];
                        break;
                    case 1:
                        destImg(i, j, c) = bmpPtr[4 * (wid * j + i) + 1];
                        break;
                    case 2:
                        destImg(i, j, c) = bmpPtr[4 * (wid * j + i) + 2];
                        break;
                }
            }
        }

    }
    return destImg;
}

SimpleBitmap ResizeBitmap::ConvertToBMP(cimg_library::CImg<unsigned char> img) {
    auto wid = img.width();
    auto hei = img.height();
    SimpleBitmap bmpOut;
    bmpOut.Create(wid, hei);
    auto dest_bmpPtr = bmpOut.GetEditableBitmapPointer();
    for (int i = 0; i < hei; i++) {
        for (int j = 0; j < wid; j++) {
            dest_bmpPtr[4 * (wid * i + j) + 0] = img.atXY(j, i, 0);
            dest_bmpPtr[4 * (wid * i + j) + 1] = img.atXY(j, i, 1);
            dest_bmpPtr[4 * (wid * i + j) + 2] = img.atXY(j, i, 2);
            // dest_bmpPtr[4*(wid*j+i)+3]=img.atXY(j,i,0);
        }
    }
    return bmpOut;
}

void ResizeBitmap::ResizeBmp(SimpleBitmap bmp, SimpleBitmap &resizedBmp, int wid, int hei) {
    resizedBmp.CleanUp();
    auto resized_CImg = ConvertToCImg(bmp).resize(wid, hei);
    resizedBmp = ConvertToBMP(resized_CImg);
    resizedBmp.Invert();
}

