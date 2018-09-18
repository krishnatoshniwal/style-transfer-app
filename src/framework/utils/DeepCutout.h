#ifndef PROJECT_DEEPCUTOUT_H
#define PROJECT_DEEPCUTOUT_H

#include "ImageUI.h"
#include "button.h"

void DrawLines();

void TransferStyleToContent();

void TransferStyleToAll();

void AddNewStyleIfPresent();

void AddNewContentIfPresent();

void ChangeStyle(int direction);

class DeepCutout {
public:
    ButtonUI btUI;

    void Initialise() {
        bmpHash.BuildHash();
        print("Going to update output image");
        ImgSet::UpdateImgSetFromBmpHash();
        ImgSet::UpdateAndShowOutputImage();  //  ** very expensive
        print("Setting UI parameters");

        ImgSet::SetUIParameters();
        print("Initialising buttons");

        btUI.Initialise();
//        TransferStyleToContent();
    }

    //
    bool Interval(Event event) {
        // Check window change here also check for key in here
        bool changesToBmp;

        int key, mx, my;
        bool clicked;

        event.GetEvent(key, mx, my, clicked);

//        std::cout << "mx: " << mx << " my: " << my << "\n";
        bool btRedraw = btUI.Interval(mx, my, clicked);

        if (key == FSKEY_LEFT) {
            ChangeStyle(-1);
            ImgSet::UpdateAndShowOutputImage();  //  ** very expensive
        } else if (key == FSKEY_RIGHT) {
            ChangeStyle(1);
            ImgSet::UpdateAndShowOutputImage();  //  ** very expensive
        } else if (key == FSKEY_UP) {
            BmpLocations::IncrementContentNum();
            bmpHash.UpdateContentBmp();
            ImgSet::UpdateAndShowOutputImage();  //  ** very expensive

        } else if (key == FSKEY_DOWN) {
            BmpLocations::DecrementContentNum();
            bmpHash.UpdateContentBmp();
            ImgSet::UpdateAndShowOutputImage();  //  ** very expensive
        }

        ImgSet::SetUIParameters();


        bool reDraw = btRedraw;
        return reDraw;
    }

    bool DrawAlways() {

        btUI.Draw();
        DrawLines();
    }

    bool Draw() {
        // TODO call SetUI parameters if the window size changes
        ImgSet::ShowImgs();
    }
};

#endif //PROJECT_DEEPCUTOUT_H
