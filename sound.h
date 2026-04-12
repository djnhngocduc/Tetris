#pragma once
#include<SDL.h>
#include<SDL_mixer.h>
using namespace std;

class sound {
private:

public:
    void Audio_long(const char* nameSong);
    void Audio_short(const char* nameSong);
};
