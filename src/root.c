#include "stdio.h"
#include "stdlib.h"
#include "root.h"

cwgRootFrame *cwgRootInit(char *title, int width, int height) {
    cwgRootFrame    *root = malloc(sizeof(cwgRootFrame));
    
    if (width && height) {
        root->width = width;
        root->height = height;
    } else {
        root->width = CWG_DEFAULT_WINDOW_WIDTH;
        root->height = CWG_DEFAULT_WINDOW_HEIGHT;
    }

    SDL_Init(SDL_INIT_VIDEO);
    root->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, root->width, root->height, SDL_WINDOW_SHOWN);
    root->renderer = SDL_CreateRenderer(root->window, -1, 0);
    return root;
}

void cwgRootMainloop(cwgRootFrame *root) {
    int         quit = 0;
    SDL_Event   event;

    while (!quit) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }
}

void cwgDestroyRoot(cwgRootFrame *root) {
    SDL_DestroyWindow(root->window);
    free(root);
}