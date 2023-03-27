#include "SDL.h"

#define CWG_DEFAULT_WINDOW_HEIGHT   160
#define CWG_DEFAULT_WINDOW_WIDTH    90

// the main frame in window
typedef struct cwgRootFrame {
    SDL_Window  *window;
    int         width;
    int         height;
} cwgRootFrame;

// initialize the root frame and window with specified title, width and height
// width and height are scaled automatically to elements when any of them is set to 0
cwgRootFrame *cwgRootInit(char *title, int width, int height);

// run mainloop of the gui
void cwgRootMainloop(cwgRootFrame *root);

// destroy and freeup memory
void cwgDestroyRoot(cwgRootFrame *root);
