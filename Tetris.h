#pragma once
#ifndef TETRIS_H_
#define TETRIS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>
#include "textbox.h"
#include "sound.h"

class Tetris {
public:
	Tetris() {
		window = NULL;
		render = NULL;
		back1 = NULL;
		blocks = NULL;
		back2 = NULL;
		imgplay1 = NULL;
		imgplay2 = NULL;
		inhelp1 = NULL;
		inhelp2 = NULL;
		backBtn = NULL;
		srcR.x = 0;
		srcR.y = 0;
		srcR.w = BlockW;
		srcR.h = BlockH;
		destR.x = 0;
		destR.y = 0;
		destR.w = BlockW;
		destR.h = BlockH;
		inback1 = false;
		running = false;
		gameOver = false;
		for (int i = 0; i < Lines; i++) {
			for (int j = 0; j < Cols; j++) matrix[i][j] = 0;
		}
		color = 1;
		move = 0;
		score = 0;
		ispaused = false;
		wait = true;
		rotate = false;
		isPlayed = false;
		delay = 300;
		startTime = 0, currentTime = 0;

		choosingTheme = false;
		currentTheme = CLASSIC;
		highScores["Classic"] = 0;
		highScores["Neon"] = 0;
		highScores["Retro"] = 0;
	}

	~Tetris() {}

	void setCurrentTime(Uint32 t);

	bool Tetrisrunning();
	bool Tetrisback1();
	void Setback1(bool x);
	bool Tetrisvalid();
	bool init(const char* name);
	void Loadingback1();

	void Randomblocks();

	void handleEvents();
	void SetPosRect(SDL_Rect& rect, int x = 0, int y = 0, int w = BlockW, int h = BlockH);
	void Moveblocks(SDL_Rect& rect, int x, int y); // Di chuyen cac khoi block

	void Gameplay();

	void GameOver();
	void UpdateRender();

	void Clean();
	bool TetrisWait();

	void SaveHighScore();
	void LoadHighScore();

	void ChooseTheme();
	void ApplyTheme();

	bool isChoosingTheme() const {
		return choosingTheme;
	}

	void GameOverScreen(bool& goBackToMenu, bool& playAgain);
	void Reset();

	bool isGameOver();

	string GetExeDir();

private:
	enum {
		ScreenW = 600,
		ScreenH = 800
	};
	enum {
		BlockW = 36,
		BlockH = 36
	};
	enum {
		Lines = 20,
		Cols = 10
	};
	enum Theme { CLASSIC, NEON, RETRO };
	bool choosingTheme;
	Theme currentTheme;
	map<string, int> highScores;


	SDL_Window* window;
	SDL_Renderer* render;
	SDL_Texture* back1, * blocks, * back2, * imgplay1, * imgplay2, * inhelp1, * inhelp2, * backBtn;
	SDL_Rect srcR, destR;

	bool inback1, running, gameOver;
	int matrix[Lines][Cols];
	static const int shapes[7][4];
	struct Point {
		int x, y;
	}
	items[4], backup[4];
	textbox txb1, txb2, txb_gameover, inhelp, txb_high1, txb_high2, classic, neon, retro;

	sound Sound;
	int xpos, ypos;
	int color, move, score;
	bool ispaused, wait, rotate, isPlayed;
	unsigned int delay;
	Uint32 startTime, currentTime;
};

#endif // TETRIS_H_