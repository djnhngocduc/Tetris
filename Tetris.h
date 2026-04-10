#pragma once
#ifndef TETRIS_H_
#define TETRIS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>
using namespace std;

class Tetris {
public:
	Tetris() {
		for (int i = 0; i < Lines; i++) {
			for (int j = 0; j < Cols; j++) matrix[i][j] = 0;
		}

		highScores["Classic"] = 0;
		highScores["Neon"] = 0;
		highScores["Retro"] = 0;

	}
	bool Tetrisvalid();

	void Gameplay();

	void GameOver();
	void UpdateRender();

	void Clean();

	string GetExeDir();

	void SaveHighScore();
	void LoadHighScore();

	void GameOverScreen(bool& goBackToMenu, bool& playAgain);
	void Reset();

	bool isGameOver();

private:
	enum {
		Lines = 20,
		Cols = 10
	};

	bool ispaused, gameOver, rotate, running;

	map<string, int> highScores;

	int matrix[Lines][Cols];
	static const int shapes[7][4];
	struct Point {
		int x, y;
	} items[4], backup[4];

	int move, color, score;
	Uint32 startTime, currentTime;
	unsigned int delay;
};

#endif // TETRIS_H_