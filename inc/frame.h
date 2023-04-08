#include "SDL.h"
#include "stdio.h"
#include "stdlib.h"

#define CWG_DEFAULT_WINDOW_HEIGHT   90
#define CWG_DEFAULT_WINDOW_WIDTH    160
#define CWG_DEFAULT_COLOR_RGB       0xc0   

// color information - (r)ed, (g)reen, (b)lue, (a)lpha
typedef struct cwgColor {
    int r;
    int g;
    int b;
    int a;
} cwgColor;

// just to include pointer to same struct inside
typedef struct cwgFrame cwgFrame;
// standard frame
// autowidth and autoheight are booleans
struct cwgFrame {
    int         row;
    int         column;
    int         width;
    int         height;
    int         autowidth;
    int         autoheight;
    SDL_Rect    *background;
    cwgFrame    *children;
    int         childrenCount;
    cwgColor    *color;
};

// the main frame in window
typedef struct cwgRootFrame {
    SDL_Window      *window;
    SDL_Renderer    *renderer;
    cwgFrame        *frame;
    int             width;
    int             height;
} cwgRootFrame;

// initialize the root frame and window with specified title, width and height
// width and height are scaled automatically to elements when any of them is set to 0
cwgRootFrame *cwgRootInit(char *title, int width, int height);

// run mainloop of the gui
void cwgRootMainloop(cwgRootFrame *root);

// destroy and freeup memory
void cwgDestroyRoot(cwgRootFrame *root);

// set renderer color to default grey
void cwgSetDefaultColor(cwgRootFrame *root);

// create a new frame
// width and height can be set to 0 - then their size will be auto scaled
cwgFrame *cwgCreateFrame(int width, int height);

// place a frame in the another frame
void cwgPlaceFrame(cwgFrame *newFrame, cwgFrame *rootFrame, int row, int column);
