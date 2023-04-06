#define SDL_MAIN_HANDLED

#include "stdio.h"
#include "frame.h"

int main(int argc, char **argv) {
    printf("hello!\n");

    cwgRootFrame *root = cwgRootInit("gui window", 400, 400);

    cwgFrame *frame1 = cwgCreateFrame(100, 100);
    cwgFrame *frame2 = cwgCreateFrame(100, 100);

    cwgRootMainloop(root);

    return 0;
}