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

	game->state = GAME_RUNNING;
	game->time = 0;
	game->scrollX = 0;
	game->boy.dx = 0;
	game->boy.dy = 0;
	game->boy.x = 100;
	game->boy.y = 300;
	game->boy.onLedge = 0;
	game->boy.faceLeft = 0;

}

void loadGame(game_t *game){

	//init window and renderer
	game->window = SDL_CreateWindow("Alone", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W,WINDOW_H,0);
	game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//textures
	SDL_Surface *tmp = IMG_Load("resources/images/map.png");
	game->mapText = SDL_CreateTextureFromSurface(game->renderer, tmp);
	SDL_FreeSurface(tmp);

	SDL_Surface *tmp2 = IMG_Load("resources/images/brick.png");
	game->brick = SDL_CreateTextureFromSurface(game->renderer, tmp2);
	SDL_FreeSurface(tmp2);
	for(int i=0; i<50; ++i){
		game->ledges[i].w = 170;
		game->ledges[i].h = 64;
		game->ledges[i].x = i*(300 + (rand() % 50-i)); //(340 + (rand() % (390 – 340 + 1))); 356
		game->ledges[i].y = (450 + (rand() % 50));
	}

	SDL_Surface *boy[2];
	boy[0] = IMG_Load("resources/images/boyStanding.png");
	boy[1] = IMG_Load("resources/images/boy_running.png");
	game->boyText[0] = SDL_CreateTextureFromSurface(game->renderer, boy[0]);
	game->boyText[1] = SDL_CreateTextureFromSurface(game->renderer, boy[1]);
	SDL_FreeSurface(boy[0]);
	SDL_FreeSurface(boy[1]);


}

void quit(game_t *game){
	SDL_DestroyTexture(game->boyText[0]);
	SDL_DestroyTexture(game->boyText[1]);
	SDL_DestroyTexture(game->brick);
	SDL_DestroyTexture(game->mapText);
	SDL_DestroyRenderer(game->renderer);
	SDL_DestroyWindow(game->window);
	TTF_Quit();
	SDL_Quit();
}


 #endif //LOAD_H_ 
