//#include <iostream>
#include "sdlui.h"

using namespace std;

int main() {
    short cell[20][20] = {{}};
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    Mix_Init(0);

    menuStart();




    return 0;
}
