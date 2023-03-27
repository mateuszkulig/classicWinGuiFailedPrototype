#include "stdio.h"

#define SDL_MAIN_HANDLED

#include "root.h"

int main(int argc, char **argv) {
    printf("hello!\n");

    cwgRootFrame *root = cwgRootInit("gui window", 400, 400);
    cwgRootMainloop(root);

    return 0;
}