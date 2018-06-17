#include "libraries.h"
#include "ImageUI.h"

using namespace std;


typedef bool (*FuncPtr)(void);

class Button {
public:
    int x, y, wid, hei;
    std::string name;
    bool mouseOnButton;
    FuncPtr fP;


    void Set(std::string incoming, int given_x, int given_y, int width, int height, bool (*functocall)(void));

    void Set(std::string incoming, ImageLocations imgLocs, bool (*functocall)(void));

    Button(){
        wid = 150; hei = 22;
    }

    Button(std::string incoming, int given_x, int given_y, int width, int height, bool (*functocall)(void));

    ~Button();

    void CleanUp(void);

    int CheckButton(int mx, int my);

    void Draw();
};


bool doAction(void);


//bool (*functocall)(void) = &doAction;

bool B1Action(void);

bool B2Action(void);

bool B3Action(void);

bool B4Action(void);

class ButtonUI {
    /**
     * ButtonUI: collection of all the buttons
     */
protected:
public:
    // update style images - ADD STYLE
    // update content image - ADD IMAGE
    // transfer style - GO
    // get output for all styles - ALL IN!

    std::vector<Button> buttons;
    bool isAllIn;

    void Initialise();

    void Draw();

    bool Interval(int mx, int my, bool clicked);

    ~ButtonUI() { CleanUp(); }

    void CleanUp() { buttons.clear(); }
};
