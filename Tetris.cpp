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