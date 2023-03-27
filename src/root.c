#include "stdio.h"
#include "root.h"

void rootInit() {
    cwgRootFrame root;
    SDL_Init(SDL_INIT_VIDEO);
    root.window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 160, 90, SDL_WINDOW_SHOWN);
}