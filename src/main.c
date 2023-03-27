#include "stdio.h"

#define SDL_MAIN_HANDLED

#include "root.h"

int main(int argc, char **argv) {
    printf("hello!\n");
    rootInit();
    return 0;
}