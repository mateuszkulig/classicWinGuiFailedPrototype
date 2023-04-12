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
    } else {
        result->autoheight = 1;
    }

    result->background = malloc(sizeof(SDL_Rect));
    result->children = NULL;
    result->childrenCount = 0;

    result->color = malloc(sizeof(cwgColor));
    result->color->r = CWG_DEFAULT_COLOR_RGB;
    result->color->g = CWG_DEFAULT_COLOR_RGB;
    result->color->b = CWG_DEFAULT_COLOR_RGB;
    result->color->a = SDL_ALPHA_OPAQUE;
    
    return result;
}

void cwgPlaceFrame(cwgFrame *newFrame, cwgFrame *rootFrame, int row, int column) {
    int x = 0, y = 0;

    if (rootFrame->childrenCount == 0) {
        x = 0;
    // } else if (row > rootFrame->childrenCount) {
    //         printf("got in the loop\n");
    //         x += rootFrame->children[rootFrame->childrenCount - 1]->x;
    //         x += rootFrame->children[rootFrame->childrenCount - 1]->width;
    } else {
        for (size_t i=0; i<row-1; ++i) {
            x += rootFrame->children[i]->width;
        }
    }

    newFrame->row = row;
    newFrame->column = column;
    newFrame->x = x;
    newFrame->y = 0;

    newFrame->background->x = newFrame->x;
    newFrame->background->y = newFrame->y;
    newFrame->background->w = newFrame->width;
    newFrame->background->h = newFrame->height;


    rootFrame->childrenCount++;
    rootFrame->children = realloc(rootFrame->children, (rootFrame->childrenCount) * sizeof(cwgFrame*));
    rootFrame->children[rootFrame->childrenCount - 1] = newFrame;
}

void cwgUpdateRoot(cwgRootFrame *root) {
    for (size_t i=0; i<(root->frame->childrenCount); ++i) {

        // printf("%d\n", root->frame->children[i].width);

        SDL_SetRenderDrawColor(
            root->renderer,
            root->frame->children[i]->color->r,
            root->frame->children[i]->color->g,
            root->frame->children[i]->color->b,
            root->frame->children[i]->color->a
        );
        SDL_RenderFillRect(root->renderer, root->frame->children[i]->background);
        SDL_RenderPresent(root->renderer);
    }
}
