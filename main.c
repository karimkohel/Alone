#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <math.h>
#include "game.h"
#include "init&load&quit.h"

int main(int argc, char const *argv[]){

	//init game state 
	game_t game;

	//init everything
	initGame(&game);
	//load everything
	loadGame(&game);

	while( game.gamestate == GAME_RUNNING ){
		SDL_SetRenderDrawColor(game.renderer, MAX, MAX, MAX, MAX);
		SDL_RenderClear(game.renderer);
		SDL_RenderPresent(game.renderer);
	}

	//quit everything
	quit(&game);

	return 0;
}