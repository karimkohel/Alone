#ifndef EVENTS_H_
#define EVENTS_H_ 

void getEvents(game_t *game){

	SDL_Event event;

	while(SDL_PollEvent(&event)){

		if(event.type == SDL_QUIT){
			game->state = GAME_CLOSED;
		}
		else if(event.type == SDL_KEYDOWN){

			switch(event.key.keysym.sym){
				case SDLK_ESCAPE:
					//till now we will quit but after menu implementation we will get to menu by escape
					game->state = GAME_CLOSED;
					break;
				case SDLK_SPACE:
					if(game->boy.onLedge){
						game->boy.dy = -8;
						game->boy.onLedge = 0;
					}
					break;

			}

		}

	}

	const Uint8 *state = SDL_GetKeyboardState(NULL);

	// fluid movements
	if(state[SDL_SCANCODE_LEFT]){
		game->boy.dx -= 0.5;
		game->boy.faceLeft = 1;
		if(game->boy.dx < -5)
			game->boy.dx = -5;
	}
	else if(state[SDL_SCANCODE_RIGHT]){
		game->boy.dx += 0.5;
		game->boy.faceLeft = 0;
		if(game->boy.dx > 5)
			game->boy.dx = 5;
	}
	else{
		// if he is slowing down use friction
		game->boy.animFrame = 0; //standing animation
		game->boy.dx *= 0.8f;
		if(fabsf(game->boy.dx) < 0.1)
			game->boy.dx = 0;
	}

	//more jumping
	if(state[SDL_SCANCODE_SPACE]){
		game->boy.dy -= 0.12;
	}
	
}

 #endif //EVENTS_H_
