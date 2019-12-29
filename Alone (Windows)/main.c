#include <stdio.h>
#include "resources/dlls/SDL.h"
#include "resources/dlls/SDL_image.h"
#include "resources/dlls/SDL_ttf.h"
#include "resources/dlls/SDL_mixer.h"
#include <math.h>
#include "resources/headers/game.h"
#include "resources/headers/sidescreens.h"
#include "resources/headers/init&load&quit.h"
#include "resources/headers/events.h"
#include "resources/headers/render.h"
#include "resources/headers/physics.h"

//init game state 
game_t game;

int main(int argc, char *argv[]){

	//init everything
	initGame(&game);
	//load everything
	loadGame(&game);

	if(menu(&game) == 1){
		game.state = GAME_CLOSED;
	}

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