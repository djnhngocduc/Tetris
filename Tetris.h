#pragma once
#ifndef TETRIS_H_
#define TETRIS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>

class Tetris {
public:
	Tetris() {
		
	}

private:
	enum {
		Lines = 20,
		Cols = 10
	};

	enum Theme {
		CLASSIC, 
		NEON, 
		RETRO
	};

	bool choosingTheme;
	Theme currentTheme;
	map<string, int> highScores;

	int matrix[Lines][Cols];
	static const int shapes[7][4];
	struct Point {
		int x, y;
	} items[4], backup[4];
};

#endif // TETRIS_H_