#define SDL_MAIN_HANDLED

#include "stdio.h"
#include "frame.h"

int main(int argc, char **argv) {
    printf("hello!\n");

    cwgRootFrame *root = cwgRootInit("gui window", 400, 400);

    cwgFrame *frame1 = cwgCreateFrame(100, 100);
    cwgFrame *frame2 = cwgCreateFrame(100, 100);
    cwgFrame *frame3 = cwgCreateFrame(100, 100);

    frame1->color->r = 255;
    frame1->color->g = 20;
    frame1->color->b = 147;
    frame1->color->a = 255;

    frame2->color->r = 0;
    frame2->color->g = 255;
    frame2->color->b = 0;
    frame2->color->a = 255;

    frame3->color->r = 0;
    frame3->color->g = 0;
    frame3->color->b = 255;
    frame3->color->a = 255;

    cwgPlaceFrame(frame1, root->frame, 1, 1);
    cwgPlaceFrame(frame2, root->frame, 2, 1);
    cwgPlaceFrame(frame3, root->frame, 3, 1);
    
    printf("%d\n", frame2->background->w);

    cwgUpdateRoot(root);

    cwgRootMainloop(root);

    return 0;
}