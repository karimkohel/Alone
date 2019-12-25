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

			}

		}

	}
}

 #endif //EVENTS_H_
