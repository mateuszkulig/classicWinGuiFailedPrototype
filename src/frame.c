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
        cwgUpdateRoot(root);
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
    root->frame->width = width;
    root->frame->height = height;
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

    result->background = malloc(sizeof(SDL_Rect));
    result->children = NULL;
    result->childrenCount = 0;

    result->color = malloc(sizeof(cwgColor));
    result->color->r = CWG_DEFAULT_COLOR_RGB;
    result->color->g = CWG_DEFAULT_COLOR_RGB;
    result->color->b = CWG_DEFAULT_COLOR_RGB;
    result->color->a = SDL_ALPHA_OPAQUE;
    
    if (width) {
        result->width = width;
        result->background->w = width;
        result->autowidth = 0;
    } else {
        result->autowidth = 1;
        result->background->w = 0;
        result->width = 0;
    }

    if (height) {
        result->height = height;
        result->autoheight = 0;
    } else {
        result->autoheight = 1;
    }

    return result;
}

void cwgReplaceFrames(cwgFrame *root) {
    int freespace = root->width;
    int autoChildren = 0;
    int autoSpace;
    int takenX = 0;

    cwgSortFramesByRow(root);
    for (size_t i = 0; i<root->childrenCount; ++i) {
        if (root->children[i]->autowidth) {
            autoChildren++;
        } else {
            freespace -= root->children[i]->width;
        }
    }

    if (autoChildren) {
        autoSpace = freespace / autoChildren;
    } else {
        autoSpace = freespace;
    }

    for (size_t i = 0; i<root->childrenCount; ++i) {
        root->children[i]->x = takenX;
        root->children[i]->background->x = takenX;
        if (root->children[i]->autowidth) {
            root->children[i]->width = autoSpace;
            root->children[i]->background->w = autoSpace;
            takenX += autoSpace;
        } else {
            takenX += root->children[i]->width;
        }
    }
}

void cwgSortFramesByRow(cwgFrame *root) {
    int         completed;
    cwgFrame    *temp = NULL;

    if (root->childrenCount < 2) {return;}
    
    do {
        completed = 1;
        for (size_t i=1; i<root->childrenCount; ++i) {
            if (root->children[i]->row < root->children[i-1]->row) {
                completed = 0;
                temp = root->children[i];
                root->children[i] = root->children[i-1];
                root->children[i-1] = temp;
            }
        }
    } while (!completed);
}

void cwgPlaceFrame(cwgFrame *newFrame, cwgFrame *rootFrame, int row, int column) {
    rootFrame->childrenCount++;
    rootFrame->children = realloc(rootFrame->children, (rootFrame->childrenCount) * sizeof(cwgFrame*));
    rootFrame->children[rootFrame->childrenCount - 1] = newFrame;

    newFrame->row = row;
    newFrame->column = column;

    cwgReplaceFrames(rootFrame);

    newFrame->y = 0;
    newFrame->background->y = newFrame->y;;
    newFrame->background->h = newFrame->height;
}

void cwgUpdateRoot(cwgRootFrame *root) {
    for (size_t i=0; i<(root->frame->childrenCount); ++i) {
        SDL_SetRenderDrawColor(
            root->renderer,
            root->frame->children[i]->color->r,
            root->frame->children[i]->color->g,
            root->frame->children[i]->color->b,
            root->frame->children[i]->color->a
        );
        SDL_RenderFillRect(root->renderer, root->frame->children[i]->background);
    }
    SDL_RenderPresent(root->renderer);
}
