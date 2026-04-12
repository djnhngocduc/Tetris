#include <iostream>
#include <fstream>
#include <windows.h>
#include "Tetris.h"

using namespace std;

const int Tetris::shapes[7][4] = {
    0,1,2,3,
    0,1,5,6,
    0,4,5,6,
    1,2,5,6,
    1,4,5,6,
    2,1,5,4,
    2,6,5,4,
};
void Tetris::setCurrentTime(Uint32 t) {
    currentTime = t;
}

bool Tetris::Tetrisrunning() {
    return running;
}

bool Tetris::Tetrisback1() {
    return inback1;
}

void Tetris::Setback1(bool x) {
    inback1 = x;
}

bool Tetris::Tetrisvalid() {
    //ktra va cham 
    for (int i = 0; i < 4; i++)
        if (items[i].x < 0 || items[i].x >= Cols || items[i].y >= Lines) {
            //va cham matrix
            return false;
        }
        else {
            if (matrix[items[i].y][items[i].x]) {
                //va cham vs block
                return false;
            }
        }
    return true;
}


bool Tetris::init(const char* name) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
        window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenW, ScreenH, SDL_WINDOW_SHOWN);
        if (window != NULL) {
            render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (render != NULL) {
                SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
                int imgFlags = IMG_INIT_PNG;
                int initted = IMG_Init(imgFlags);
                if ((initted & imgFlags) != imgFlags) {
                    cout << "Failed to init required png support\n" << "IMG_Init() Error : " << IMG_GetError() << endl;
                }

                back2 = IMG_LoadTexture(render, "img/background2.png");
                blocks = IMG_LoadTexture(render, "img/blocks.png");
                back1 = IMG_LoadTexture(render, "img/background1.jpg");
                imgplay1 = IMG_LoadTexture(render, "img/imgplay1.png");
                imgplay2 = IMG_LoadTexture(render, "img/imgplay2.png");
                inhelp1 = IMG_LoadTexture(render, "img/help1.png");
                inhelp2 = IMG_LoadTexture(render, "img/help.jpg");
                backBtn = IMG_LoadTexture(render, "img/back.png");

                if (TTF_Init() != 0) {
                    cout << TTF_GetError();
                }

                LoadHighScore();

                txb1.Loadtext("UTM Cookies.ttf", 45);
                txb2.Loadtext("UTM Cookies.ttf", 45);
                txb_high1.Loadtext("UTM Cookies.ttf", 45);
                txb_high2.Loadtext("UTM Cookies.ttf", 45);
                txb_gameover.Loadtext("UTM Cookies.ttf", 80);

                txb1.Setcolor(255, 213, 128, 0);
                txb2.Setcolor(255, 213, 128, 0);
                txb_high1.Setcolor(255, 213, 128, 0);
                txb_high2.Setcolor(255, 213, 128, 0);
                txb_gameover.Setcolor(255, 99, 71, 0);

                txb1.Settext("SCORE: ", render);
                txb2.Settext("0", render);
                txb_high1.Settext("HIGH: ", render);
                txb_gameover.Settext("Game over", render);

                Randomblocks();
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }

    inback1 = true;
    running = true;
    return true;
}

void Tetris::Loadingback1() {
    SDL_GetMouseState(&xpos, &ypos);
    SDL_RenderCopy(render, back1, NULL, NULL);

    SDL_Rect dst1;
    dst1.x = 20;
    dst1.y = 70;
    dst1.w = 135;
    dst1.h = 88;

    SDL_Rect dst;
    dst.x = 450;
    dst.y = 70;
    dst.w = 135;
    dst.h = 88;


    if (450 <= xpos && xpos <= (135 + 450) && 40 <= ypos && ypos <= (40 + 88)) {
        Sound.Audio_short("sound/play.wav");
        SDL_RenderCopy(render, imgplay2, NULL, &dst);
        SDL_RenderPresent(render);
    }
    else {
        SDL_RenderCopy(render, imgplay1, NULL, &dst);
    }

    if (20 <= xpos && xpos <= (135 + 20) && 70 <= ypos && ypos <= (70 + 88)) {
        // render cach choi
        SDL_RenderCopy(render, inhelp2, NULL, NULL);
    }
    else {
        SDL_RenderCopy(render, inhelp1, NULL, &dst1);
    }

    if (!isPlayed) {
        Sound.Audio_long("sound/background1.mp3");
        isPlayed = true;
    }

    SDL_RenderPresent(render);
}
void Tetris::Randomblocks() {
    color = 1 + rand() % 7;
    int n = rand() % 7;
    for (int i = 0; i < 4; i++) {
        items[i].x = shapes[n][i] % 4;
        items[i].y = shapes[n][i] / 4;
    }
}

void Tetris::handleEvents() {
    SDL_Event m;
    while (SDL_PollEvent(&m)) {
        if (running) {
            switch (m.type) {
            case SDL_QUIT:
                running = false;
                wait = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&xpos, &ypos);
                if (450 <= xpos && xpos <= (135 + 450) && 70 <= ypos && ypos <= (70 + 88)) {
                    choosingTheme = true;
                    Setback1(false);
                }
                break;
            case SDL_KEYDOWN:
                switch (m.key.keysym.sym) {
                case SDLK_UP:
                    rotate = true;
                    Sound.Audio_short("sound/move.wav");
                    break;
                case SDLK_LEFT:
                    move = -1;
                    Sound.Audio_short("sound/move.wav");
                    break;
                case SDLK_RIGHT:
                    move = 1;
                    Sound.Audio_short("sound/move.wav");
                    break;
                case SDLK_SPACE:
                    ispaused = !ispaused;
                default:
                    break;
                }
            default:
                break;
            }
        }
    }
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_DOWN]) delay = 20;
}

void Tetris::ChooseTheme() {
    bool selecting = true;

    textbox txClassic, txNeon, txRetro;
    txClassic.Loadtext("UTM Cookies.ttf", 50);
    txNeon.Loadtext("UTM Cookies.ttf", 50);
    txRetro.Loadtext("UTM Cookies.ttf", 50);

    txClassic.Setcolor(100, 100, 100, 255);
    txNeon.Setcolor(57, 255, 20, 255);
    txRetro.Setcolor(180, 100, 255, 255);

    txClassic.Settext("Classic Theme", render);
    txNeon.Settext("Neon Theme", render);
    txRetro.Settext("Retro Theme", render);

    SDL_Rect backRect = { 20, 20, 50, 50 };

    while (selecting) {
        SDL_RenderClear(render);
        SDL_RenderCopy(render, back1, NULL, NULL);

        txClassic.Draw(render, 200, 200);
        txNeon.Draw(render, 200, 300);
        txRetro.Draw(render, 200, 400);
        SDL_RenderCopy(render, backBtn, NULL, &backRect);

        SDL_RenderPresent(render);

        SDL_Event m;
        while (SDL_PollEvent(&m)) {
            switch (m.type) {
            case SDL_QUIT:
                running = false;
                wait = false;
                selecting = false;
                break;

            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&xpos, &ypos);
                if (xpos >= 20 && xpos <= 70 && ypos >= 20 && ypos <= 70) {
                    Setback1(true);
                    selecting = false;
                }
                if (xpos >= 200 && xpos <= 200 + 300) {
                    if (ypos >= 200 && ypos <= 250) {
                        currentTheme = CLASSIC;
                        ApplyTheme();
                        selecting = false;
                    }
                    else if (ypos >= 300 && ypos <= 350) {
                        currentTheme = NEON;
                        ApplyTheme();
                        selecting = false;
                    }
                    else if (ypos >= 400 && ypos <= 450) {
                        currentTheme = RETRO;
                        ApplyTheme();
                        selecting = false;
                    }
                }
                break;
            }
        }

        SDL_Delay(10);
    }
}

void Tetris::ApplyTheme() {
    Mix_HaltMusic();

    Mix_Music* music = Mix_LoadMUS("sound/background2(Unwelcome_School).wav");
    Mix_VolumeMusic(15);
    Mix_PlayMusic(music, -1);

    if (currentTheme == CLASSIC) {
        back2 = IMG_LoadTexture(render, "img/background_classic.png");
    }
    else if (currentTheme == NEON) {
        back2 = IMG_LoadTexture(render, "img/background_neon.png");
    }
    else if (currentTheme == RETRO) {
        back2 = IMG_LoadTexture(render, "img/background2.png");
    }
    string theme;
    if (currentTheme == CLASSIC) {
        theme = "Classic";
    }
    else if (currentTheme == NEON) {
        theme = "Neon";
    }
    else if (currentTheme == RETRO) {
        theme = "Retro";
    }
    txb_high2.Settext(to_string(highScores[theme]), render);
    choosingTheme = false;
    Setback1(false);
}


void Tetris::SetPosRect(SDL_Rect& rect, int x, int y, int w, int h) {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

void Tetris::Moveblocks(SDL_Rect& rect, int x, int y) {
    rect.x += x;
    rect.y += y;
}


void Tetris::Gameplay() {
    gameOver = true;
    // backup
    if (ispaused == true) return;
    for (int i = 0; i < 4; i++) {
        backup[i] = items[i];  // save block khi va cham
    }
    //move
    for (int i = 0; i < 4; i++) {
        items[i].x += move;
    }
    if (!Tetrisvalid()) {   // xu li va cham khi move
        for (int i = 0; i < 4; i++) {
            items[i] = backup[i];
        }
    }
    // rotate
    if (rotate) {
        Point p = items[2]; //// center of rotation
        for (int i = 0; i < 4; i++) {
            int x = items[i].y - p.y;
            int y = items[i].x - p.x;
            items[i].x = p.x - x;
            items[i].y = p.y + y;
        }
        if (!Tetrisvalid()) { // xu ly va cham khi rotate
            for (int i = 0; i < 4; i++) {
                items[i] = backup[i];
            }
        }
    }


    // tick
    if (currentTime - startTime > delay) {
        for (int i = 0; i < 4; i++) backup[i] = items[i];
        for (int i = 0; i < 4; i++) items[i].y++;
        if (!Tetrisvalid()) {
            for (int i = 0; i < 4; i++) matrix[backup[i].y][backup[i].x] = color;
            Randomblocks();
        }
        startTime = currentTime;
    }

    // check lines
    int k = Lines - 1;
    for (int i = k; i > 0; i--) {
        int count = 0;
        for (int j = 0; j < Cols; j++) {
            if (matrix[i][j]) count++;
            matrix[k][j] = matrix[i][j];
        }
        if (count < Cols) k--;
        if (count == Cols) {
            Sound.Audio_short("sound/clear.wav");
            score += 100;
            string text = to_string(score);
            txb2.Settext(text, render);
        }
    }
    move = 0;
    rotate = false;

    if (score >= 3000) delay = 300;
    else if (score >= 2000) delay = 500;
    else if (score >= 1000) delay = 700;
    else delay = 1000;
}

void Tetris::GameOver() {
    int game_over_count = 0;
    for (int i = 0; i < Lines; i++) {
        for (int j = 0; j < Cols; j++) {
            if (matrix[i][j] != 0) {
                game_over_count++;
                break;
            }
        }
    }
    if (game_over_count == Lines) {
        string theme;
        if (currentTheme == CLASSIC) {
            theme = "Classic";
        }
        else if (currentTheme == NEON) {
            theme = "Neon";
        }
        else if (currentTheme == RETRO) {
            theme = "Retro";
        }
        if (score > highScores[theme]) {
            highScores[theme] = score;
            SaveHighScore();
        }
        running = false;
    }
}

void Tetris::UpdateRender() {
    if (ispaused == true) return;
    SDL_RenderCopy(render, back2, NULL, NULL);
    txb1.Draw(render, 450, 300);
    txb2.Draw(render, 450, 350);
    txb_high1.Draw(render, 450, 400);
    txb_high2.Draw(render, 450, 450);

    //va cham vs day ( luu hinh anh cuoi cung khi o day - bao gom ca mau sac)
    for (int i = 0; i < Lines; i++) {
        for (int j = 0; j < Cols; j++) {
            if (matrix[i][j]) {
                SetPosRect(srcR, matrix[i][j] * BlockW);  // Giu nguyen mau cua block khi dang o day
                SetPosRect(destR, j * BlockW, i * BlockH);
                Moveblocks(destR, BlockW, ScreenH - (Lines + 1) * BlockH);
                SDL_RenderCopy(render, blocks, &srcR, &destR);
            }
        }
    }

    //Tao block
    for (int i = 0; i < 4; i++) {
        SetPosRect(srcR, color * BlockW);
        SetPosRect(destR, items[i].x * BlockW, items[i].y * BlockH);
        Moveblocks(destR, BlockW, ScreenH - (Lines + 1) * BlockH);
        SDL_RenderCopy(render, blocks, &srcR, &destR);
    }

    SDL_RenderPresent(render);

}
bool Tetris::TetrisWait() {
    return wait;
}

// chong tran bo nho
void Tetris::Clean() {
    SDL_DestroyTexture(blocks);
    SDL_DestroyTexture(back2);
    SDL_DestroyTexture(backBtn);
    SDL_DestroyRenderer(render);
    IMG_Quit();
    SDL_Quit();
}

string Tetris::GetExeDir() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    string fullPath(buffer);
    return fullPath.substr(0, fullPath.find_last_of("\\/") + 1);
}

void Tetris::LoadHighScore() {
    string path = GetExeDir() + "highscore.txt";
    ifstream file(path);
    string theme;
    int score;
    if (file.is_open()) {
        while (file >> theme >> score) {
            highScores[theme] = score;
        }
        file.close();
    }
}

void Tetris::SaveHighScore() {
    string path = GetExeDir() + "highscore.txt";
    ofstream file(path);
    if (file.is_open()) {
        for (auto& pair : highScores) {
            file << pair.first << " " << pair.second << endl;
        }
        file.close();
    }
}

void Tetris::GameOverScreen(bool& goBackToMenu, bool& playAgain) {
    Mix_HaltMusic();

    Mix_Music* music = Mix_LoadMUS("sound/gameover.wav");
    Mix_VolumeMusic(45);
    Mix_PlayMusic(music, 0);

    textbox txAgain, txBack;

    txAgain.Loadtext("UTM Cookies.ttf", 50);
    txAgain.Setcolor(255, 255, 255, 255);
    txAgain.Settext("Again", render);

    txBack.Loadtext("UTM Cookies.ttf", 50);
    txBack.Setcolor(255, 255, 255, 255);
    txBack.Settext("Back", render);

    SDL_Rect againRect = { 380, 450, 200, 60 }, backRect = { 100, 450, 200, 60 };

    bool waiting = true;
    while (waiting) {
        SDL_RenderClear(render);
        SDL_RenderCopy(render, back1, NULL, NULL);
        txb_gameover.Draw(render, 100, 50);
        txb1.Draw(render, 200, 150);
        txb2.Draw(render, 350, 150);
        txAgain.Draw(render, againRect.x, againRect.y);
        txBack.Draw(render, backRect.x, backRect.y);
        SDL_RenderPresent(render);

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                wait = false;
                waiting = false;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mx, my;
                SDL_GetMouseState(&mx, &my);
                if (mx >= againRect.x && mx <= againRect.x + againRect.w && my >= againRect.y && my <= againRect.y + againRect.h) {
                    playAgain = true;
                    waiting = false;
                }
                if (mx >= backRect.x && mx <= backRect.x + backRect.w && my >= backRect.y && my <= backRect.y + backRect.h) {
                    goBackToMenu = true;
                    waiting = false;
                }
            }
        }
    }
}

void Tetris::Reset() {
    memset(matrix, 0, sizeof(matrix));
    score = 0;
    move = 0;
    rotate = false;
    delay = 1000;
    ispaused = false;
    startTime = 0;
    Randomblocks();

    string text = to_string(score);
    txb2.Settext(text, render);

    string theme;
    if (currentTheme == CLASSIC) {
        theme = "Classic";
    }
    else if (currentTheme == NEON) {
        theme = "Neon";
    }
    else {
        theme = "Retro";
    }
    txb_high2.Settext(to_string(highScores[theme]), render);
    running = true;
    gameOver = false;
}

bool Tetris::isGameOver() {
    return gameOver;
}
