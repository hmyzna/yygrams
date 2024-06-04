#include "sdlui.h"
#include <iostream>

using namespace std;

void readNono(short *sln[15][15], string fileName, int *m, int *n) {
    ifstream in("1.nono");
    string line;
    *m = 0; *n = 0;
    bool firstrun = true;
    while (getline(in,line)) {
        if (firstrun) {
            *n = line.length();
            firstrun = false;
        }
        for (int i = 0; i < line.length(); i++) {
            *sln[*m][i] = line[i] - '0';
        }
        //cout << "счит " << line << endl;
        //cout << "факт ";
        //for (int i = 0; i < *n; ++i) {
        //    cout << *sln[*m][i];
        //} //cout << endl;
        *m = *m + 1;
    }

}

void renderTimer(int x, int y, unsigned int time, TTF_Font* font, SDL_Renderer* rend, bool darkMode) {
    unsigned int timeInSeconds = time / 1000;
    unsigned int min = timeInSeconds / 60, sec = timeInSeconds % 60;
    string timerString = "time: " + to_string(min) + ":" + to_string(sec);
    if (sec/10 == 0) timerString = "time: " + to_string(min) + ":0" + to_string(sec);
    SDL_Surface* textSurface;
    if (darkMode) textSurface = TTF_RenderText_Blended(font, timerString.c_str(), {230,230,230});
    else textSurface = TTF_RenderText_Blended(font, timerString.c_str(), {25,25,25});


    SDL_Texture* text = SDL_CreateTextureFromSurface(rend, textSurface);
    int textWidth = textSurface->w;
    int textHeight = textSurface->h;
    SDL_FreeSurface(textSurface);
    SDL_Rect renderQuad = { x, y, textWidth, textHeight };
    SDL_RenderCopy(rend, text, nullptr, &renderQuad);
    SDL_DestroyTexture(text);
}

void renderHint(int x, int y, short value, TTF_Font* font, SDL_Renderer* rend, bool darkMode) {
    SDL_Rect outline = {x,y,24,24};
    SDL_Rect insidepart = {x+1,y+1,22,22};


    string valstr = to_string(value);
    SDL_Surface* textSurface;
    if (darkMode) textSurface = TTF_RenderText_Blended(font, valstr.c_str(), {110,110,110});
    else textSurface = TTF_RenderText_Blended(font, valstr.c_str(), {65,65,65});

    if (darkMode) {
        SDL_SetRenderDrawColor(rend, 40, 40, 40, 0);
        SDL_RenderFillRect(rend, &outline);
        SDL_SetRenderDrawColor(rend, 50, 50, 50, 0);
        SDL_RenderFillRect(rend, &insidepart);
    }
    else {
        SDL_SetRenderDrawColor(rend, 180, 180, 180, 0);
        SDL_RenderFillRect(rend, &outline);
        SDL_SetRenderDrawColor(rend, 210, 210, 210, 0);
        SDL_RenderFillRect(rend, &insidepart);
    }

    SDL_Texture* text = SDL_CreateTextureFromSurface(rend, textSurface);
    int textWidth = textSurface->w;
    int textHeight = textSurface->h;
    SDL_Rect renderQuad = { x, y, 22, 22 };

    SDL_RenderCopy(rend, text, nullptr, &renderQuad);
    SDL_DestroyTexture(text);
}

void renderCell(int x, int y, short state, SDL_Renderer* rend, bool darkMode) {
    SDL_Rect outline = {x,y,24,24};
    SDL_Rect insidepart = {x+1,y+1,22,22};

    switch (state) {
        case 0:
        {
            if (darkMode) {
                SDL_SetRenderDrawColor(rend, 120, 120, 120, 0);
                SDL_RenderFillRect(rend, &outline);
                SDL_SetRenderDrawColor(rend, 30, 30, 30, 0);
                SDL_RenderFillRect(rend, &insidepart);
            }
            else {
                SDL_SetRenderDrawColor(rend, 130, 130, 130, 0);
                SDL_RenderFillRect(rend, &outline);
                SDL_SetRenderDrawColor(rend, 230, 230, 230, 0);
                SDL_RenderFillRect(rend, &insidepart);
            }
            break;
        }
        case 1:
        {
            if (darkMode) {
                SDL_SetRenderDrawColor(rend, 130, 130, 130, 0);
                SDL_RenderFillRect(rend, &outline);
                SDL_SetRenderDrawColor(rend, 230, 230, 230, 0);
                SDL_RenderFillRect(rend, &insidepart);
            }
            else {

                SDL_SetRenderDrawColor(rend, 120, 120, 120, 0);
                SDL_RenderFillRect(rend, &outline);
                SDL_SetRenderDrawColor(rend, 30, 30, 30, 0);
                SDL_RenderFillRect(rend, &insidepart);
            }
            break;
        }
    }
}




void renderButton(SDL_Renderer* rend, bool darkMode, menuButton but) {
    SDL_Rect outline = but.pos;
    outline.x = but.pos.x - 2;
    outline.y = but.pos.y - 2;
    outline.w = but.pos.w + 4;
    outline.h = but.pos.h + 4;
    if (darkMode) {
        SDL_SetRenderDrawColor(rend, 120, 120, 120, 0);
        SDL_RenderFillRect(rend, &outline);
        SDL_SetRenderDrawColor(rend, 30, 30, 30, 0);
        SDL_RenderFillRect(rend, &but.pos);
    }
    else {
        SDL_SetRenderDrawColor(rend, 130, 130, 130, 0);
        SDL_RenderFillRect(rend, &outline);
        SDL_SetRenderDrawColor(rend, 230, 230, 230, 0);
        SDL_RenderFillRect(rend, &but.pos);
    }
}

bool isClicked(int x, int y, SDL_Rect dest) {
    if (x >= dest.x && x < dest.x+dest.w) {
        if (y >= dest.y && y < dest.y+dest.h) {
            return true;
        }
    }
    return false;
}


int menuStart() {
    Uint32 flags = SDL_WINDOW_SHOWN;
    bool darkMode = false;
    SDL_Window* win = SDL_CreateWindow("Menu",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          400, 600, flags);
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, 0);
    SDL_SetRenderDrawColor(rend, 250, 250, 250, 0);
    SDL_RenderClear(rend);

    TTF_Font* font = TTF_OpenFont("mononoki.ttf", 70);


    menuButton toggleDarkMode;
    toggleDarkMode.pos = {50, 10, 300, 70};
    //renderButton(rend, darkMode, toggleDarkMode);
    //SDL_RenderPresent(rend);

    menuButton toggleMusic;
    toggleMusic.pos = {50, 90, 300, 70};


    SDL_Event ev;
    bool quit = false;

    while(!quit) {
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) quit = true;
            if (ev.type == SDL_MOUSEBUTTONDOWN &&
               ev.button.button == SDL_BUTTON_LEFT)
            {
                if (isClicked(ev.button.x, ev.button.y, toggleDarkMode.pos)) {
                    if (darkMode) darkMode = false;
                    else darkMode = true;
                }
                if (isClicked(ev.button.x, ev.button.y, toggleMusic.pos)) {
                    SDL_HideWindow(win);
                    game(darkMode);
                    SDL_ShowWindow(win);
                }
            }
        }



        if (darkMode) {
            SDL_SetRenderDrawColor(rend, 30, 30, 30, 0);
            SDL_RenderClear(rend);
        }
        else {
            SDL_SetRenderDrawColor(rend, 250, 250, 250, 0);
            SDL_RenderClear(rend);
        }
        renderButton(rend, darkMode, toggleDarkMode);
        renderButton(rend, darkMode, toggleMusic);


        SDL_RenderPresent(rend);
        SDL_Delay(33);
    }



    //SDL_Delay(3000);
    // завершение работы чееек
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}


int game(bool darkMode) {
    Uint32 flags = SDL_WINDOW_SHOWN;
    SDL_Window* win = SDL_CreateWindow("Menu",
                                       SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                       600, 600, flags);
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, 0);
    TTF_Font* font = TTF_OpenFont("mononoki.ttf", 30);


    menuButton toggleDarkMode;
    toggleDarkMode.pos = {250, 20, 30, 30};


    int offsetX = 230;
    int offsetY = 230;

    short cell[15][15] = {{}};
    short sln[15][15] = {{}};
    short *slnptr[15][15];
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            slnptr[i][j] = &sln[i][j];
        }
    }
    int m = 15;
    int n = 15;
    readNono(slnptr,"ff",&m,&n);
    int hintm = m/2 + (m%2);
    int hintn = n/2 + (n%2);
    //cout << m << " " << n << endl;

    // Определение чисел cверху
    int justALittleCounter = 0;

    int maxTopHint = 0;
    short topHints[8][15] = {{0}};
    for (int j = 0; j < n; ++j) {
        justALittleCounter = 0;
        int temp1 = hintm-1;
        bool flag = false;
        for (int i = (m-1); i >= 0; --i) {
            if (sln[i][j] == 1) {
                topHints[temp1][j] += 1;
                if (flag != true) justALittleCounter++;
                flag = true;
            }
            else if (flag == true) {
                flag = false;
                temp1--;
            }
        }
        if (justALittleCounter > maxTopHint) maxTopHint = justALittleCounter;
    }

    int maxLeftHint = 0;
    short leftHints[15][8] = {{0}};
    for (int i = 0; i < m; ++i) {
        justALittleCounter = 0;
        int temp1 = hintn-1;
        bool flag = false;
        for (int j = (n-1); j >= 0; --j) {
            if (sln[i][j] == 1) {
                leftHints[i][temp1] += 1;
                if (flag != true) justALittleCounter++;
                flag = true;
            }
            else if (flag == true) {
                flag = false;
                temp1--;
            }
        }
        if (justALittleCounter > maxLeftHint) maxLeftHint = justALittleCounter;
    }

    // вывод для проверки работы
    /*
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            cout << sln[i][j];
        }
        cout << endl;
    }


    cout << endl;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 15; ++j) {
            cout << topHints[i][j] << "\t";
        }
        cout << endl;
    }

    cout << endl;
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 8; ++j) {
            cout << leftHints[i][j] << "\t";
        }
        cout << endl;
    }*/
    cout << "FFFFFFF ";
    cout << maxTopHint << " " << maxLeftHint;

    SDL_Rect temp;
    unsigned int t1 = SDL_GetTicks();
    unsigned int t2 = SDL_GetTicks();
    SDL_Event ev;
    bool quit = false;




    while(!quit) {
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) quit = true;
            if (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT)
            {
                if (isClicked(ev.button.x, ev.button.y, toggleDarkMode.pos)) {
                    if (darkMode) darkMode = false;
                    else darkMode = true;
                }
                for (int i = 0; i < m; i++) {
                    for (int j = 0; j < n; j++) {
                        temp = { offsetX+j*24, offsetY+i*24,24,24 };
                        if (isClicked(ev.button.x, ev.button.y, temp)) {
                            switch (cell[i][j]) {
                                case 0:
                                    cell[i][j] = 1;
                                    break;
                                case 1:
                                    cell[i][j] = 0;
                                    break;
                            }
                        }
                    }
                }
            }
        }





        t2 = SDL_GetTicks();
        if (darkMode) {
            SDL_SetRenderDrawColor(rend, 30, 30, 30, 0);
            SDL_RenderClear(rend);
        }
        else {
            SDL_SetRenderDrawColor(rend, 250, 250, 250, 0);
            SDL_RenderClear(rend);
        }
        renderTimer(5,10,t2-t1,font,rend,darkMode);
        renderButton(rend, darkMode, toggleDarkMode);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < maxLeftHint; j++) {
                if (leftHints[i][j+(8-maxLeftHint)] != 0) {
                    renderHint(offsetX-maxLeftHint*24+j*24,offsetY+i*24, leftHints[i][j+(8-maxLeftHint)],font,rend,darkMode);
                }
            }
        }

        for (int j = 0; j < n; j++) {
            for (int i = 0; i < maxTopHint; i++) {
                if (topHints[i+(8-maxTopHint)][j] != 0) {
                    renderHint(offsetX+j*24,offsetY-maxTopHint*24+i*24, topHints[i+(8-maxTopHint)][j],font,rend,darkMode);
                }
            }
        }


        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                renderCell(offsetX+j*24, offsetY+i*24, cell[i][j], rend, darkMode);
            }
        }


        SDL_RenderPresent(rend);
        SDL_Delay(31); // это где-то 30 кадров в секунду чтоб ноутбук не перегревался
    }
    //SDL_Delay(3000);

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    return 1;
}