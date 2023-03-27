#include "SDL.h"

#define CWG_DEFAULT_WINDOW_HEIGHT   160
#define CWG_DEFAULT_WINDOW_WIDTH    90

// the main frame in window
typedef struct cwgRootFrame {
    SDL_Window  *window;
    int         width;
    int         height;
} cwgRootFrame;

// initialize the root frame and window with specified width and height
void rootInit();
