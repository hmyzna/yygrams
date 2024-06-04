#ifndef YYGRAMS_SDLUI_H
#define YYGRAMS_SDLUI_H

#include <fstream>
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

struct gameCell {
    /*
    0 - просто пустая клетка, 1 - закрашенная клетка
    2 - пустая клетка, закрашенная пользователем
    3 - закрашенная клетка, закрашенная пользователем
    */
    short s = 0;
};

struct menuButton {
    SDL_Rect pos = {0, 0, 0, 0};
    bool sel = false;
};

int menuStart();

int game(bool darkMode);

#endif //YYGRAMS_SDLUI_H
