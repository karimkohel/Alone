#ifndef LOAD_H_
#define LOAD_H_

void resetGame(game_t *game){
	initLivesScreen(game);
	game->state = GAME_INIT;
	game->time = 0;
	game->boy.dx = 0;
	game->boy.dy = 0;
	game->boy.x = 100;
	game->boy.y = 300;
	game->boy.onLedge = 0;
	game->boy.isDead = 0;
	game->deathCountDown = -1;
} 

void initGame(game_t *game){

	//init API
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		SDL_Log("Unabel to init SDL : %s", SDL_GetError());

	if(TTF_Init() < 0)
		SDL_Log("Unabel to init Fonts : %s", SDL_GetError());

	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) < 0)
		SDL_Log("Unabel to init Sound : %s", SDL_GetError());

	game->state = GAME_INIT;
	game->time = 0;
	game->deathCountDown = -1; //signifies we are not using it
	game->scrollX = 0;
	game->boy.dx = 0;
	game->boy.dy = 0;
	game->boy.x = 100;
	game->boy.y = 300;
	game->boy.onLedge = 0;
	game->boy.faceLeft = 0;
	game->boy.lives = 3;
	game->boy.isDead = 0;

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
	for(int i=0; i<100; ++i){
		game->ledges[i].w = 170;
		game->ledges[i].h = 64;
		game->ledges[i].x = i*(200 + (rand() % 70-i));//(min + (rand() % (max – min + 1))); random places
		game->ledges[i].y = (450 + (rand() % 50));
	}

	SDL_Surface *tmp3 = IMG_Load("resources/images/ghost.png");
	game->ghostText = SDL_CreateTextureFromSurface(game->renderer, tmp3);
	SDL_FreeSurface(tmp3);
	for(int i=0; i<50; ++i){
		game->ghost[i].w = 80;
		game->ghost[i].h = 130;
		game->ghost[i].x = i*(550 + (rand() % 151)); //(min + (rand() % (max – min + 1)));random places
		game->ghost[i].y = (70 + (rand() % 50));
	}

	SDL_Surface *boy[2];
	boy[0] = IMG_Load("resources/images/boyStanding.png");
	boy[1] = IMG_Load("resources/images/boy_running.png");
	game->boyText[0] = SDL_CreateTextureFromSurface(game->renderer, boy[0]);
	game->boyText[1] = SDL_CreateTextureFromSurface(game->renderer, boy[1]);
	SDL_FreeSurface(boy[0]);
	SDL_FreeSurface(boy[1]);


	//font
	game->font = TTF_OpenFont("resources/fonts/yesterday.ttf", 38);

	//init game
	initLivesScreen(game);


}

void quit(game_t *game){
	SDL_DestroyTexture(game->ghostText);
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
