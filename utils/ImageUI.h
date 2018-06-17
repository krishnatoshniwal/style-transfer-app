//
// Created by krishna on 4/28/18.
//

#ifndef PROJECT_IMAGEUI_H
#define PROJECT_IMAGEUI_H

#include <essentials.h>
#include "images.h"

class ImageUI {
public:
    double xStartRatio, xEndRatio, imageHeightRatio, imageWidthRatio, yRatio;
    int numImages;
    vector<ImageLocations> imgLocs;

    void SetImageUILocs();

    void SetStyleImages(vector<Images> &styleImages, int centreImage);

    void SetBigImages(Images &contentImage, Images &styleImage, Images &outputImage);
};

// To Get the centre window index
void GetWindowIdx(int numIdx, int centreIdx, int windowSize, vector<int> &toReturn);


namespace ImgSet {
    /**
     * Contains all the Images that are located in bmpHash. Update it from UpdateImgSetFromBmpHash
     * Once the hash is built
     *
     */

    extern bool contentPresent, stylePresent, outputPresent;
    extern int nStyleImages, maxStyleImgs;
    extern int centreImage; // access centreImage directly to change the image

    extern vector<Images> styleImages;
    extern Images contentImage, styleImage, outputImage;
    extern ImageUI styleUIParameters, bigUIParameters;

    void SetUIParameters();

    void UpdateImgSetFromBmpHash();

    inline void ShowImgs() {
        for (auto &stImage : styleImages) {
            stImage.ShowImageInUI();
        }

        contentImage.ShowImageInUI();
        styleImage.ShowImageInUI();
        outputImage.ShowImageInUI();
    }

    inline void UpdateCentreImage(int num) {
        // TODO make it cleaner
        bmpHash.SetStyleBmp(num);
        centreImage = num;
    }

    inline void ShowOutputImage() { outputImage.ShowImage(); }

    inline void HideOutputImage() { outputImage.HideImage(); }

    inline void ChangeToRight() {
        centreImage = (centreImage + 1) % nStyleImages;
        bmpHash.SetStyleBmp(centreImage);
        UpdateImgSetFromBmpHash();
        SetUIParameters();
    }

    inline void ChangeToLeft() {
        centreImage = (centreImage - 1 + nStyleImages) % nStyleImages;
        bmpHash.SetStyleBmp(centreImage);
        UpdateImgSetFromBmpHash();
        SetUIParameters();
    }


    // Button Placement functions

    inline ImageLocations GetContentImageLocs() {
        /**
         * New content image
         */
        return bigUIParameters.imgLocs[0];
    }

    inline ImageLocations GetStyleImageLocs() {
        /**
         * Go button placement
         */
        return bigUIParameters.imgLocs[1];
    }

    inline ImageLocations GetOutputImageLocs() {
        /**
         * All In placement
         */
        return bigUIParameters.imgLocs[2];
    }

    inline ImageLocations AllStylesImageLocs() {
        /**
         * Update style button placement
         */
        return styleUIParameters.imgLocs[2];
    }

    inline void UpdateAndShowOutputImage() {
        std::string outputPath, outputName;
        bmpHash.GetOutputFileForCurrent(outputPath, outputName);
        ImgSet::HideOutputImage();

        if (fileExists(outputPath)) {
            bmpHash.UpdateOutputBmp(outputPath, outputName);
            ImgSet::ShowOutputImage();
        }
        ImgSet::UpdateImgSetFromBmpHash();

    }
};

#endif //PROJECT_IMAGEUI_H
