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