#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <math.h>
#include "game.h"
#include "init&load&quit.h"
#include "events.h"
#include "render.h"
#include "physics.h"

//init game state 
game_t game;

int main(){

	//init everything
	initGame(&game);
	//load everything
	loadGame(&game);

	while( game.state != GAME_CLOSED ){
		getEvents(&game);
		render(&game);
		process(&game);
		detectCollision(&game);
	}

	//quit everything
	quit(&game);

	return 0;
}