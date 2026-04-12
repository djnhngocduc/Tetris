#include "Tetris.h"
#include <iostream>
#include <ctime>

using namespace std;

#undef main
int main(int argc, char* argv[]) {
    srand(static_cast<unsigned int>(time(0)));
    Tetris* game = new Tetris();
    sound Sound;
    const char* name = "Tetris";
    game->init(name);
    while (game->TetrisWait()) {
        while (game->Tetrisrunning()) {
            game->setCurrentTime(SDL_GetTicks());
            game->handleEvents();

            if (game->Tetrisback1()) {
                game->Loadingback1();
            }
            else if (game->isChoosingTheme()) {
                game->ChooseTheme();
            }
            else {
                game->Gameplay();
                game->UpdateRender();
            }
            game->GameOver();
        }

        if (game->isGameOver()) {
            bool goBackToMenu = false, playAgain = false;
            game->GameOverScreen(goBackToMenu, playAgain);
            Mix_HaltMusic();

            if (goBackToMenu) {
                game->Setback1(true);
                Sound.Audio_long("sound/background1.mp3");
            }

            if (playAgain) {
                game->Setback1(false);
                Mix_Music* music = Mix_LoadMUS("sound/background2(Unwelcome_School).wav");
                Mix_VolumeMusic(15);
                Mix_PlayMusic(music, -1);
            }
            game->Reset();
        }

        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                break;
            }
        }
    }
    game->Clean();
    return 0;
}