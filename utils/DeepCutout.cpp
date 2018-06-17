//
// Created by krishna on 4/2/18.
//

#include "DeepCutout.h"

// Function declaration done earlier in button.h
bool B1Action(void) {

    print("Finding style images, please wait...");
    AddNewStyleIfPresent();
    print("Done");
    return true;
}

bool B2Action(void) {
    print("Finding content images, please wait...");
    AddNewContentIfPresent();
    print("Done");
    return true;
}

bool B3Action(void) {
    TransferStyleToContent();
    return true;
}

bool B4Action(void) {
    TransferStyleToAll();
    return true;
}

void TransferStyleToContent() {
    /**
     * The CRUX of the entire project!
     * BONUS: Also updates the output bmp in the hashset
     */
    std::string outputPath, outputName;
    bmpHash.GetOutputFileForCurrent(outputPath, outputName);
    if (!fileExists(outputPath)) {
        CToPy(bmpHash.GetContentPath(), bmpHash.GetStylePath(), bmpHash.GetOutputPath(), 0, 0, 0, 0);
    }
    ImgSet::UpdateAndShowOutputImage();
}

void AddNewStyleIfPresent() {
    bmpHash.UpdateStyleBmps();
}

void TransferStyleToAll() {
    for (int i = 0; i < ImgSet::nStyleImages; i++) {
        TransferStyleToContent();
        ChangeStyle(1);
    }
}

void AddNewContentIfPresent() {
    bmpHash.UpdateContentBmp();
}

void ChangeStyle(int direction) {
    /**
     * Changes the style according to the direction
     * left = -1
     * right = +1
     */
    if (direction == -1) {
        ImgSet::ChangeToLeft();
    } else if (direction == +1) {
        ImgSet::ChangeToRight();
    }
}


void DrawLines() {
    int widLeave = 10;
    int widLine = GetCurrentWidth(1.0) - 2 * widLeave;
    int heiLine1 = GetCurrentHeight(0.62);
    int heiLine2 = GetCurrentHeight(0.65);
//    std::cout << "widLine: " << widLine << " heiLine: " << heiLine1 << "\n";
//    glRasterPos2i(widLeave+widLine-70, heiLine2);
//    auto c_str = num2str<int>(2);
//    std::string String = static_cast<ostringstream*>( &(ostringstream() << widLine) )->str();

//    std::ostringstream ss;
//    ss << widLine;
//    YsGlDrawFontBitmap12x16(ss.str().c_str());

    glBegin(GL_LINES);
    glVertex2i(widLeave, heiLine1);
    glVertex2i(widLeave + widLine, heiLine1);
    glVertex2i(widLeave, heiLine2);
    glVertex2i(widLeave + widLine, heiLine2);
    glEnd();

    std::string stFont = "Style Images";
    glColor3ub(0, 0, 0);
    glRasterPos2i(widLeave + widLine / 2 - 13 * stFont.length() / 2, heiLine2 - 3);
    YsGlDrawFontBitmap12x16(stFont.c_str());
    glColor3ub(0, 0, 0);
}