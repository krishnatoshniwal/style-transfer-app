//
// Created by krishna on 4/28/18.
//

#ifndef PROJECT_IMAGES_H
#define PROJECT_IMAGES_H

#include "essentials.h"
#include "bmphash.h"

class Images {
    // The Images class that
private:
    std::string bmpKey;
    std::string imgName;
    SimpleBitmap bmp, bmp2show;
    bool hidden, updateScale;
    double scale[2] = {1, 1}; // imHeight / bmpHei;
    int x, y, imHeight, imWidth;

public:

    Images() : hidden(true), updateScale(false) {};

    ~Images();

    void CopyFrom(const std::string &bmpKey);

    void CleanUp();

    void UpdateScale();

    void Resize();

    // Draw Image

    void ShowImageInUI();

    // Set methods
    void ForceUpdateScale() { updateScale = true; }

    void Set(int x, int y, int imHeight, int imWidth);

    void HideImage() { hidden = true; }

    void ShowImage() { hidden = false; }

    void SetName(std::string name) { imgName = name; };

    // Get Methods

    std::string GetBmpKey() const { return bmpKey; }

    std::string GetName() const { return imgName; }

    void SavePng() const {
        FILE *fp = fopen(imgName.c_str(), "wb");
        bmp.SavePng(fp);
    }
};

class ImageLocations {
public:
    int x, y, imWidth, imHeight;

    // sets the image locs as defined
    void SetImageLocs(Images &image);
};
#endif //PROJECT_IMAGES_H
