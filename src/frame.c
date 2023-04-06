#include "frame.h"

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
    SDL_DestroyRenderer(root->renderer);
    SDL_DestroyWindow(root->window);
    free(root->frame->background);
    free(root->frame);
    free(root);
}

void cwgSetDefaultColor(cwgRootFrame *root) {
    SDL_SetRenderDrawColor(
        root->renderer, 
        CWG_DEFAULT_COLOR_RGB, 
        CWG_DEFAULT_COLOR_RGB, 
        CWG_DEFAULT_COLOR_RGB, 
        SDL_ALPHA_OPAQUE
        );
}

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
    root->renderer = SDL_CreateRenderer(root->window, -1, SDL_RENDERER_ACCELERATED);
    
    root->frame = malloc(sizeof(cwgFrame));
    root->frame->background = malloc(sizeof(SDL_Rect));
    root->frame->background->x = 0;
    root->frame->background->y = 0;
    root->frame->background->w = root->width;
    root->frame->background->h = root->height;

    cwgSetDefaultColor(root);
    SDL_RenderFillRect(root->renderer, root->frame->background);
    
    SDL_RenderPresent(root->renderer);

    return root;
}

cwgFrame *cwgCreateFrame(int width, int height) {
    cwgFrame *result = malloc(sizeof(cwgFrame));
    if (width) {
        result->width = width;
        result->autowidth = 0;
    } else {
        result->autowidth = 1;
    }

    if (height) {
        result->height = height;
        result->autoheight = 0;
    }

    result->background = malloc(sizeof(SDL_Rect));
    result->children = NULL;
    
    return result;
}
