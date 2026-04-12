#include "sound.h"
#include <iostream>

using namespace std;

void sound::Audio_long(const char* song) {
	Mix_Music* music = NULL;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
		cout << Mix_GetError();
	}
	music = Mix_LoadMUS(song);
	if (music == NULL) {
		cout << Mix_GetError();
	}
	if (!Mix_PlayingMusic()) {
		Mix_PlayMusic(music, -1);
	}
}

void sound::Audio_short(const char* song) {
	Mix_Chunk* inlist = NULL;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
		cout << Mix_GetError();
	}
	inlist = Mix_LoadWAV(song);
	if (inlist == NULL) {
		cout << Mix_GetError();
	}
	if (!Mix_Playing(-1)) {
		Mix_PlayChannel(-1, inlist, 0);
	}
}
