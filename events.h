#ifndef EVENTS_H_
#define EVENTS_H_ 

void getEvents(game_t *game){

	SDL_Event event;

	const Uint8 *state = SDL_GetKeyboardState(NULL);

	// fluid movements
	if(state[SDL_SCANCODE_LEFT]){
		game->boy.x -= 7;
	}
	else if(state[SDL_SCANCODE_RIGHT]){
		game->boy.x += 7;
	}
	// else{
	// 	//if he is slowing down use friction
	// 	// game->boy.animFrame = 0; //standing animation
	// 	game->boy.dx *= 0.8f;
	// 	if(fabsf(game->boy.dx) < 0.1)
	// 		game->boy.dx = 0;
	// }

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

			}

		}

	}
}

 #endif //EVENTS_H_
