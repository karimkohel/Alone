#ifndef LOAD_H_
#define LOAD_H_ 

void initGame(game_t *game){

	//init API
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		SDL_Log("Unabel to init SDL : %s", SDL_GetError());

	if(TTF_Init() < 0)
		SDL_Log("Unabel to init Fonts : %s", SDL_GetError());

	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) < 0)
		SDL_Log("Unabel to init Sound : %s", SDL_GetError());
}

void loadGame(game_t *game){

	//init window and renderer
	game->window = SDL_CreateWindow("Archer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 650,650,0);
	game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void quit(game_t *game){
	SDL_DestroyRenderer(game->renderer);
	SDL_DestroyWindow(game->window);
	SDL_Quit();
}


 #endif 
