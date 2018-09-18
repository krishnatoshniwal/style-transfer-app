//
// Created by krishna on 4/28/18.
//

#include "images.h"

void Images::Set(int x, int y, int imHeight, int imWidth) {
    this->x = x;
    this->y = y;
    this->imHeight = imHeight;
    this->imWidth = imWidth;
    updateScale = true; //
}

Images::~Images() {
    bmp.CleanUp();
    bmp2show.CleanUp();
}

void Images::CopyFrom(const std::string &bmpKey) {
    /**
     * Copies from the bmpKey, assumes that bmpHash the almighty has been declared already!
     */
    CleanUp();
    bmp = bmpHash.GetBmp(bmpKey);
    imgName = bmpHash.GetNameWithoutFormat(bmpKey);
    this->bmpKey = bmpKey;
    updateScale = true;
}

void Images::CleanUp() {
    bmp.CleanUp();
    bmp2show.CleanUp();
}

void Images::ShowImageInUI() {
    if (!hidden) {
        /**
         * Might throw error if bmp2show is not present!
         */
        UpdateScale();
        glRasterPos2i(x, y);
        glDrawPixels(imWidth, imHeight, GL_RGBA, GL_UNSIGNED_BYTE, bmp2show.GetBitmapPointer());

        glColor3ub(50, 50, 200);
        glRasterPos2i(x, y - imHeight - 2);
        YsGlDrawFontBitmap12x16(imgName.c_str());
        glColor3ub(0, 0, 0);

    }
}

void Images::UpdateScale() {
    /**
     * Updates the scale of bmp2show
     * Debug help: take care of the updateScale flag!
     */
    if (updateScale) {
        auto bmpHei = bmp.GetHeight(), bmpWid = bmp.GetWidth();
        if (bmpHei == 0 || bmpWid == 0)
            print("The bmp was not loaded correctly, Error in Update Scale");
        scale[0] = imHeight / bmpHei;
        scale[1] = imWidth / bmpWid;
        Resize();
        updateScale = false;
    }
}


void Images::Resize() {
    if (bmp2show.GetWidth() != imWidth || bmp2show.GetHeight() != imHeight)
        bitmapResizer.ResizeBmp(bmp, bmp2show, imWidth, imHeight);
}


void ImageLocations::SetImageLocs(Images &image) {

    image.Set(x, y, imHeight, imWidth);
}
