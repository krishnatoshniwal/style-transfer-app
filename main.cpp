#include <essentials.h>
#include <DeepCutout.h>

class FsLazyWindowApplication : public FsLazyWindowApplicationBase {
protected:
    bool needRedraw;
    DeepCutout deepCutoutApp;
    int threshold = 4;
    bool forcedRedraw;
    int windowState = 1, windowPauseFrames = threshold;

public:
    FsLazyWindowApplication();

    virtual void BeforeEverything(int argc, char *argv[]);

    virtual void GetOpenWindowOption(FsOpenWindowOption &OPT) const;

    virtual void Initialize(int argc, char *argv[]);

    virtual void Interval(void);

    virtual void BeforeTerminate(void);

    virtual void Draw(void);

    virtual bool UserWantToCloseProgram(void);

    virtual bool MustTerminate(void) const;

    virtual long long int GetMinimumSleepPerInterval(void) const;

    virtual bool NeedRedraw(void) const;
};

FsLazyWindowApplication::FsLazyWindowApplication() {
    needRedraw = false;
}

/* virtual */ void FsLazyWindowApplication::BeforeEverything(int argc, char *argv[]) {
}

/* virtual */ void FsLazyWindowApplication::GetOpenWindowOption(FsOpenWindowOption &opt) const {
    opt.x0 = 0;
    opt.y0 = 0;
    opt.wid = windowSize::GetWidth();
    opt.hei = windowSize::GetHeight();
}

/* virtual */ void FsLazyWindowApplication::Initialize(int argc, char *argv[]) {
    deepCutoutApp.Initialise();

}


/* virtual */ void FsLazyWindowApplication::Interval(void) {


    auto key = FsInkey();
    if (FSKEY_ESC == key) {
        SetMustTerminate(true);
    }
    int lb, mb, rb, mx, my;
    auto evt = FsGetMouseEvent(lb, mb, rb, mx, my);
    bool clicked(evt == FSMOUSEEVENT_LBUTTONDOWN);


    needRedraw = deepCutoutApp.Interval(Event(key, mx, my, clicked));
    forcedRedraw = false;
    bool windowChange = CheckForWindowChange();
    if (!windowChange) {
        // Window size is not changing
        windowPauseFrames += 1;
    } else {
        // Window size is changing
        windowPauseFrames = 0;
        windowState = 1;
    }

    if (windowPauseFrames > threshold && windowState) {

        needRedraw = true;
        windowState = 0;
    }

}

/* virtual */ void FsLazyWindowApplication::Draw(void) {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    /* The idea is to freeze the window when the window size keeps changing
     * Draw with the final version itself
     * windowPause frames ensures that the draw function is called only when it exceeds the minimum frame limit
     */
    int wid, hei;
    FsGetWindowSize(wid, hei);
    windowSize::SetWidHei(wid, hei);

    if (threshold < windowPauseFrames || forcedRedraw) {
//        std::cout << "wid: " << wid << " hei: " << hei<<"\n";

        deepCutoutApp.DrawAlways();
        deepCutoutApp.Draw();
        FsSwapBuffers();
        windowPauseFrames = 0;
        // Need to set global wid and height hear
    }


    needRedraw = false;
}

/* virtual */ bool FsLazyWindowApplication::UserWantToCloseProgram(void) {
    return true; // Returning true will just close the program.
}

/* virtual */ bool FsLazyWindowApplication::MustTerminate(void) const {
    return FsLazyWindowApplicationBase::MustTerminate();
}

/* virtual */ long long int FsLazyWindowApplication::GetMinimumSleepPerInterval(void) const {
    return 10;
}

/* virtual */ void FsLazyWindowApplication::BeforeTerminate(void) {
}

/* virtual */ bool FsLazyWindowApplication::NeedRedraw(void) const {
    return needRedraw;
}

static FsLazyWindowApplication *appPtr = nullptr;

/* static */ FsLazyWindowApplicationBase *FsLazyWindowApplicationBase::GetApplication(void) {
    if (nullptr == appPtr) {
        appPtr = new FsLazyWindowApplication;
    }
    return appPtr;
}

