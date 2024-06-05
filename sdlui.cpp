#include "sdlui.h"
#include <iostream>

using namespace std;

void readNono(short *sln[15][15], string fileName, int *m, int *n) {
    ifstream in(fileName);
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

void cheat(short sln[15][15], short *cell[15][15]) {
    bool f = false;
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if ((*cell[i][j] == 0 || *cell[i][j] == 2) && sln[i][j] == 1) {
                *cell[i][j] = 1;
                f = true;
                break;
            }
        }
        if (f) break;
    }
}

bool gameWin(short sln[15][15], short cell[15][15]) {
    int c = 0;
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (cell[i][j] == sln[i][j] || ((cell[i][j] == 2) && (sln[i][j] == 0))) {
                c++;
            }
        }
    }
    if (c == 15*15) return true;
    return false;
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

void renderText(int x, int y, TTF_Font* font, string str,SDL_Renderer* rend, bool darkMode) {

    SDL_Surface* textSurface;
    if (darkMode) textSurface = TTF_RenderUTF8_Blended(font, str.c_str(), {200,200,200});
    else textSurface = TTF_RenderUTF8_Blended(font, str.c_str(), {30,30,30});


    SDL_Texture* text = SDL_CreateTextureFromSurface(rend, textSurface);
    int textWidth = textSurface->w;
    int textHeight = textSurface->h;
    SDL_FreeSurface(textSurface);
    SDL_Rect renderQuad = { x, y, textWidth, textHeight };
    SDL_RenderCopy(rend, text, nullptr, &renderQuad);
    SDL_DestroyTexture(text);

}

void renderWin(unsigned int time, TTF_Font* font, SDL_Renderer* rend, bool darkMode) {
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
    SDL_Rect renderQuad = { 0, 0, 600, 600 };
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
    int textWidth = (textSurface->w);
    int textHeight = (textSurface->h);
    SDL_Rect renderQuad = { x, y, textWidth, textHeight };
    if (value < 10) renderQuad.x+=6;

    SDL_RenderCopy(rend, text, nullptr, &renderQuad);
    SDL_DestroyTexture(text);
}

void renderCell(int x, int y, short state, SDL_Renderer* rend, bool darkMode, SDL_Texture* bc, SDL_Texture* wc) {
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
                SDL_SetRenderDrawColor(rend, 170, 170, 170, 0);
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

                SDL_SetRenderDrawColor(rend, 70, 70, 70, 0);
                SDL_RenderFillRect(rend, &outline);
                SDL_SetRenderDrawColor(rend, 30, 30, 30, 0);
                SDL_RenderFillRect(rend, &insidepart);
            }
            break;
        }
        case 2:
        {
            if (darkMode) {
                SDL_SetRenderDrawColor(rend, 120, 120, 120, 0);
                SDL_RenderFillRect(rend, &outline);
                SDL_SetRenderDrawColor(rend, 30, 30, 30, 0);
                SDL_RenderFillRect(rend, &insidepart);
                SDL_RenderCopy(rend, wc, nullptr, &outline);
            }
            else {
                SDL_SetRenderDrawColor(rend, 170, 170, 170, 0);
                SDL_RenderFillRect(rend, &outline);
                SDL_SetRenderDrawColor(rend, 230, 230, 230, 0);
                SDL_RenderFillRect(rend, &insidepart);
                SDL_RenderCopy(rend, bc, nullptr, &outline);
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
                                          400, 400, flags);
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, 0);
    SDL_SetRenderDrawColor(rend, 250, 250, 250, 0);
    SDL_RenderClear(rend);

    TTF_Font* font = TTF_OpenFont("mononoki.ttf", 50);


    menuButton toggleDarkMode;
    toggleDarkMode.pos = {50, 110, 300, 70};
    //renderButton(rend, darkMode, toggleDarkMode);
    //SDL_RenderPresent(rend);

    menuButton level1;
    level1.pos = {50, 200, 140, 70};
    menuButton level2;
    level2.pos = {210, 200, 140, 70};
    menuButton level3;
    level3.pos = {50, 290, 140, 70};
    menuButton level4;
    level4.pos = {210, 290, 140, 70};


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
                if (isClicked(ev.button.x, ev.button.y, level1.pos)) {
                    SDL_HideWindow(win);
                    game(darkMode, "1.nono");
                    SDL_ShowWindow(win);
                }
                if (isClicked(ev.button.x, ev.button.y, level2.pos)) {
                    SDL_HideWindow(win);
                    game(darkMode, "2.nono");
                    SDL_ShowWindow(win);
                }
                if (isClicked(ev.button.x, ev.button.y, level3.pos)) {
                    SDL_HideWindow(win);
                    game(darkMode, "3.nono");
                    SDL_ShowWindow(win);
                }
                if (isClicked(ev.button.x, ev.button.y, level4.pos)) {
                    SDL_HideWindow(win);
                    game(darkMode, "4.nono");
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
        renderButton(rend, darkMode, level1);

        renderButton(rend, darkMode, level2);
        renderButton(rend, darkMode, level3);
        renderButton(rend, darkMode, level4);
        renderButton(rend, darkMode, level1);
        renderButton(rend, darkMode, level1);


        renderText(60,10,font,u8"Нонограммы",rend,darkMode);

        if(darkMode) {
            renderText(87,120,font,"DarkMode",rend,darkMode);
        }
        else {
            renderText(70,120,font,"LightMode",rend,darkMode);
        }

        renderText(60,210,font,"lv.1",rend,darkMode);
        renderText(220,210,font,"lv.2",rend,darkMode);
        renderText(60,300,font,"lv.3",rend,darkMode);
        renderText(220,300,font,"lv.4",rend,darkMode);
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


int game(bool darkMode, string level) {
    Uint32 flags = SDL_WINDOW_SHOWN;
    SDL_Window* win = SDL_CreateWindow("Menu",
                                       SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                       600, 600, flags);
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, 0);
    TTF_Font* font = TTF_OpenFont("mononoki.ttf", 20);
    TTF_Font* timerFont = TTF_OpenFont("mononoki.ttf", 42);


    bool musicEnabled = true;
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_Music* musicsound = Mix_LoadMUS("heartfelt.wav");
    Mix_Chunk* winsound = Mix_LoadWAV("vika.wav");

    if (musicEnabled) {
        Mix_PlayMusic(musicsound,-1);
        Mix_VolumeMusic(40);
    }

    menuButton toggleDarkMode;
    toggleDarkMode.pos = {280, 10, 48, 48};

    menuButton exitBtn;
    exitBtn.pos = {530, 10, 48, 48};

    menuButton musicBtn;
    musicBtn.pos = {350, 10, 48, 48};

    menuButton hintBtn;
    hintBtn.pos = {420, 10, 48, 48};

    SDL_Surface *winbgimg = IMG_Load("winbg.bmp");
    SDL_SetColorKey(winbgimg, SDL_TRUE, SDL_MapRGB(winbgimg->format, 255, 255, 255));
    SDL_Texture* winbg = SDL_CreateTextureFromSurface(rend, winbgimg);
    SDL_FreeSurface(winbgimg);

    SDL_Surface *exitimg = IMG_Load("exit.bmp");
    SDL_SetColorKey(exitimg, SDL_TRUE, SDL_MapRGB(exitimg->format, 255, 255, 255));
    SDL_Texture* exittx = SDL_CreateTextureFromSurface(rend, exitimg);
    SDL_FreeSurface(exitimg);

    SDL_Surface *musicimg = IMG_Load("music.bmp");
    SDL_SetColorKey(musicimg, SDL_TRUE, SDL_MapRGB(musicimg->format, 255, 255, 255));
    SDL_Texture* musictx = SDL_CreateTextureFromSurface(rend, musicimg);
    SDL_FreeSurface(musicimg);

    SDL_Surface *mutedimg = IMG_Load("muted.bmp");
    SDL_SetColorKey(mutedimg, SDL_TRUE, SDL_MapRGB(mutedimg->format, 255, 255, 255));
    SDL_Texture* mutedtx = SDL_CreateTextureFromSurface(rend, mutedimg);
    SDL_FreeSurface(mutedimg);

    SDL_Surface *bci = IMG_Load("blackcross.bmp");
    SDL_SetColorKey(bci, SDL_TRUE, SDL_MapRGB(bci->format, 255, 255, 255));
    SDL_Texture* bctx = SDL_CreateTextureFromSurface(rend, bci);
    SDL_FreeSurface(bci);

    SDL_Surface *wci = IMG_Load("whitecross.bmp");
    SDL_SetColorKey(wci, SDL_TRUE, SDL_MapRGB(wci->format, 0, 0, 0));
    SDL_Texture* wctx = SDL_CreateTextureFromSurface(rend, wci);
    SDL_FreeSurface(wci);

    SDL_Surface *hintsurf = IMG_Load("hint.bmp");
    SDL_SetColorKey(hintsurf, SDL_TRUE, SDL_MapRGB(hintsurf->format, 255, 255, 255));
    SDL_Texture* hinttx = SDL_CreateTextureFromSurface(rend, hintsurf);
    SDL_FreeSurface(hintsurf);

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

    short *cellptr[15][15];
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            cellptr[i][j] = &cell[i][j];
        }
    }

    int m = 15;
    int n = 15;
    readNono(slnptr,level,&m,&n);
    int hintm = 8;
    int hintn = 8;
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
    }
    //cout << "FFFFFFF ";
    cout << maxTopHint << " " << maxLeftHint;

    SDL_Rect temp;
    unsigned int t1 = SDL_GetTicks();
    unsigned int t2 = SDL_GetTicks();
    SDL_Event ev;
    bool quit = false;

    bool done = false;

    bool winsoundOn = false;

    SDL_Rect box = {0,60, 600, 60};

    while(!quit) {
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) quit = true;
            if (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT)
            {
                if (isClicked(ev.button.x, ev.button.y, toggleDarkMode.pos)) {
                    if (darkMode) darkMode = false;
                    else darkMode = true;
                }
                if (isClicked(ev.button.x, ev.button.y, exitBtn.pos)) {
                    quit = true;
                }
                if (isClicked(ev.button.x, ev.button.y, musicBtn.pos)) {
                    if (musicEnabled) {
                        Mix_VolumeMusic(0);
                        musicEnabled = false;
                    }
                    else {
                        Mix_VolumeMusic(40);
                        musicEnabled = true;
                    }
                }
                if (!done) {
                    for (int i = 0; i < m; i++) {
                        for (int j = 0; j < n; j++) {
                            temp = {offsetX + j * 24, offsetY + i * 24, 24, 24};
                            if (isClicked(ev.button.x, ev.button.y, temp)) {
                                switch (cell[i][j]) {
                                    case 0:
                                        cell[i][j] = 1;
                                        break;
                                    case 1:
                                        cell[i][j] = 0;
                                        break;
                                }
                                if (gameWin(sln, cell)) done = true;

                            }
                        }
                    }
                    if (isClicked(ev.button.x, ev.button.y, hintBtn.pos)) {
                        cheat(sln, cellptr);
                        if (gameWin(sln, cell)) done = true;                    }
                }
            }
            if (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_RIGHT)
            {
                if (!done) {
                    for (int i = 0; i < m; i++) {
                        for (int j = 0; j < n; j++) {
                            temp = {offsetX + j * 24, offsetY + i * 24, 24, 24};
                            if (isClicked(ev.button.x, ev.button.y, temp)) {
                                switch (cell[i][j]) {
                                    case 0:
                                        cell[i][j] = 2;
                                        break;
                                    case 2:
                                        cell[i][j] = 0;
                                        break;
                                }
                            }
                        }
                    }
                }
            }
        }



        //if (done) cout <<"uraa!" << endl;

        if (!done) t2 = SDL_GetTicks();
        if (darkMode) {
            SDL_SetRenderDrawColor(rend, 30, 30, 30, 0);
            SDL_RenderClear(rend);
        }
        else {
            SDL_SetRenderDrawColor(rend, 250, 250, 250, 0);
            SDL_RenderClear(rend);
        }
        renderTimer(5,10,t2-t1,timerFont,rend,darkMode);
        renderButton(rend, darkMode, toggleDarkMode);
        renderButton(rend, darkMode, musicBtn);
        renderButton(rend, darkMode, exitBtn);
        renderButton(rend, darkMode, hintBtn);

        if (musicEnabled) SDL_RenderCopy(rend, musictx, nullptr, &musicBtn.pos);
        else SDL_RenderCopy(rend, mutedtx, nullptr, &musicBtn.pos);

        SDL_RenderCopy(rend, exittx, nullptr, &exitBtn.pos);

        SDL_RenderCopy(rend, hinttx, nullptr, &hintBtn.pos);
        //SDL_RenderCopy(rend, winbg, nullptr, &box);

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
                renderCell(offsetX+j*24, offsetY+i*24, cell[i][j], rend, darkMode, bctx, wctx);
            }
        }

        if (done) {
            SDL_RenderCopy(rend, winbg, nullptr, &box);
            renderText(200,65,timerFont,"You Won!",rend,true);
            if (!winsoundOn) {
                Mix_VolumeMusic(0);
                if (musicEnabled) Mix_PlayChannel(-1, winsound, 0);
                winsoundOn = true;
            }
        }


        SDL_RenderPresent(rend);
        SDL_Delay(31); // это где-то 30 кадров в секунду чтоб ноутбук не перегревался
    }
    Mix_VolumeMusic(0);
    //SDL_Delay(3000);

    Mix_FreeMusic(musicsound);
    Mix_FreeChunk(winsound);
    Mix_CloseAudio();

    SDL_DestroyTexture(winbg);
    SDL_DestroyTexture(musictx);
    SDL_DestroyTexture(mutedtx);
    SDL_DestroyTexture(exittx);

    SDL_DestroyTexture(wctx);
    SDL_DestroyTexture(bctx);
    SDL_DestroyTexture(hinttx);

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);

    return 0;
}