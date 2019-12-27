#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <math.h>
#include "resources/headers/game.h"
#include "resources/headers/sidescreens.h"
#include "resources/headers/init&load&quit.h"
#include "resources/headers/events.h"
#include "resources/headers/render.h"
#include "resources/headers/physics.h"

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