#pragma once
#include<string>
#include<SDL.h>
#include<SDL_ttf.h>

using namespace std;

class textbox {
private:
    TTF_Font* font;
    string text;
    SDL_Texture* textTexture;
    SDL_Rect dst;
    SDL_Color color;

public:
    textbox() {
        textTexture = NULL;
        color.r = 255;
        color.g = 255;
        color.b = 255;
        color.a = 0;
    }
    void Loadtext(string filepath, int size);
    void Settext(string text, SDL_Renderer* render);
    void Setcolor(int r, int g, int b, int a);
    void Draw(SDL_Renderer* render, int x, int y);
};
