#include <SDL.h>

int main(int argc, char* argv[]) {
	SDL_Window* window = SDL_CreateWindow("SETUP MY GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	while (1) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 123, 0);
		SDL_RenderClear(renderer);

		SDL_Rect rect = { 100, 100, 100, 100 };

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &rect);

		SDL_RenderPresent(renderer);
	}

	return 0;
}