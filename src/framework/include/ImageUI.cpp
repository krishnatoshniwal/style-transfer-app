//
// Created by krishna on 4/28/18.
//

#include "ImageUI.h"


void ImageUI::SetImageUILocs() {
    imgLocs.resize(numImages);
    double xEnd = GetCurrentWidth(xEndRatio), xStart = GetCurrentWidth(xStartRatio);
    double y = GetCurrentHeight(yRatio);
    double imageWidth = GetCurrentWidth(imageWidthRatio), imageHeight = GetCurrentHeight(imageHeightRatio);
    double widthTotal = xEnd - xStart;
    double widthWithoutImages = widthTotal - numImages * imageWidth;
    double widthOfSpace = widthWithoutImages / (numImages - 1);

    for (int i = 0; i < numImages; i++) {
        imgLocs[i].x = int(xStart + i * (widthOfSpace + imageWidth));
        imgLocs[i].y = int(y);
        imgLocs[i].imWidth = int(imageWidth);
        imgLocs[i].imHeight = int(imageHeight);
    }
}

void ImageUI::SetStyleImages(vector<Images> &styleImages, int centreImage) {
    vector<int> styleImagesIdx;
    GetWindowIdx(styleImages.size(), centreImage, numImages, styleImagesIdx);     // numImages is set to numStyleShow
    SetImageUILocs();
    for(auto &stImage : styleImages){
        stImage.HideImage();
    }

    for (int i = 0; i < numImages; i++) {
        int curStyleIdx = styleImagesIdx[i];
        imgLocs[i].SetImageLocs(styleImages[curStyleIdx]);
        styleImages[curStyleIdx].ShowImage();
    }
}

void ImageUI::SetBigImages(Images &contentImage, Images &styleImage, Images &outputImage) {
    // Sets the UI locs, output Image is only displayed when required
    SetImageUILocs();

    if (3 == numImages) {
        imgLocs[0].SetImageLocs(contentImage);
        contentImage.ShowImage();
        imgLocs[1].SetImageLocs(styleImage);
        styleImage.ShowImage();
        imgLocs[2].SetImageLocs(outputImage);
    } else
        std::cout << "Dimensions dont match, assigning to the correct image?";
}


void GetWindowIdx(int numIdx, int centreIdx, int windowSize, vector<int> &toReturn) {
    // Returns a window of coordinates around a centre index in a circular array
    // Ex: numIdx: 7, centreIdx: 1, windowSize: 5
    // Appends a cleared vector object with elements 6,0,1,2,3

    toReturn.clear();
    int bfrRelativeCentreIdx = -(windowSize - 1) / 2;
    int afrRelativeCentreIdx = (windowSize - 1) / 2;
    for (int i = bfrRelativeCentreIdx; i <= afrRelativeCentreIdx; i++) {
        int curEle = (centreIdx + i + numIdx) ;
        curEle = curEle % numIdx;
        toReturn.push_back(curEle);
    }
}

namespace ImgSet {
    bool contentPresent = false, stylePresent = false, outputPresent = false;
    int nStyleImages = 0, numStyleShow = 5;
    int centreImage = 0; // access centreImage directly to change the image
    vector<Images> styleImages;
    Images contentImage, styleImage, outputImage;
    ImageUI styleUIParameters, bigUIParameters;


    void SetUIParameters() {
        contentPresent = true;
        styleUIParameters.xStartRatio = 0.02;
        styleUIParameters.xEndRatio = 0.98;
        styleUIParameters.yRatio = 0.9;
        styleUIParameters.imageHeightRatio = 0.21;
        styleUIParameters.imageWidthRatio = 0.19;
        styleUIParameters.numImages = numStyleShow;

        bigUIParameters.xStartRatio = 0.01;
        bigUIParameters.xEndRatio = 0.99;
        bigUIParameters.yRatio = 0.5;
        bigUIParameters.imageHeightRatio = 0.35;
        bigUIParameters.imageWidthRatio = 0.32;
        bigUIParameters.numImages = 3;

        styleUIParameters.SetStyleImages(styleImages, centreImage);
        bigUIParameters.SetBigImages(contentImage, styleImage, outputImage);
    }

    void UpdateImgSetFromBmpHash() {
        // Update style images
        nStyleImages = bmpHash.nStyleImages;
        contentPresent = bmpHash.contentPresent;
        stylePresent = bmpHash.stylePresent;
        outputPresent = bmpHash.outputPresent;
        styleImages.resize(nStyleImages);
        if (nStyleImages > 0) {
            for (int i = 0; i < nStyleImages; i++) {
                styleImages[i].CopyFrom(bmpHash.GetStyleBmpKeyFromIndex(i));
            }
        }

        // Update content image
        if (contentPresent) {
            contentImage.CopyFrom(bmpHash.GetContentBmpKey());
        }
        if (stylePresent) {

            styleImage.CopyFrom(bmpHash.GetStyleBmpKey());
            styleImage.ShowImageInUI();
        }
        if (outputPresent) {
            outputImage.CopyFrom(bmpHash.GetOutputBmpKey());
        }
    };
}

