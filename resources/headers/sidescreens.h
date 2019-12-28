#ifndef SIDESCREEN_H_
#define SIDESCREEN_H_

//lives screen
void initLivesScreen(game_t *game){

	char str[30] = "";

	sprintf(str, "You have %d lives left", game->boy.lives);

	SDL_Color white = {MAX, MAX, MAX, MAX};

	SDL_Surface *tmp = TTF_RenderText_Blended(game->font, str, white);
	game->labelW = tmp->w;
	game->labelH = tmp->h;
	game->label = SDL_CreateTextureFromSurface(game->renderer, tmp);
	SDL_FreeSurface(tmp);
}

void renderLivesScreen(game_t *game){

	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, MAX-170);//try making it semi transparant

	SDL_RenderClear(game->renderer);

	SDL_SetRenderDrawColor(game->renderer, MAX, MAX, MAX, MAX);

	SDL_Rect textRect = {220, 350- game->labelH, game->labelW, game->labelH};
	SDL_RenderCopy(game->renderer, game->label, NULL, &textRect);
}

void quitLivesScreen(game_t *game){

	SDL_DestroyTexture(game->label);
	game->label = NULL;
}

void initGameOver(game_t *game){

	char str[] = "Please close the game because you suck.";

	SDL_Color white = {MAX, MAX, MAX, MAX};

	SDL_Surface *tmp = TTF_RenderText_Blended(game->font, str, white);
	game->labelW = tmp->w;
	game->labelH = tmp->h;
	game->label = SDL_CreateTextureFromSurface(game->renderer, tmp);
	SDL_FreeSurface(tmp);
}

void renderGameOver(game_t *game){

	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, MAX);

	SDL_RenderClear(game->renderer);

	SDL_SetRenderDrawColor(game->renderer, MAX, MAX, MAX, MAX);

	SDL_Rect textRect = {40, 250- game->labelH, game->labelW, game->labelH};
	SDL_RenderCopy(game->renderer, game->label, NULL, &textRect);
}

void quitGameOver(game_t *game){
	SDL_DestroyTexture(game->label);
	game->label = NULL;
}

void initGameWonScreen(game_t *game){

	char str[30] = "";

	sprintf(str, "You have defeated level %d", game->winCount);

	SDL_Color white = {MAX, MAX, MAX, MAX};

	SDL_Surface *tmp = TTF_RenderText_Blended(game->font, str, white);
	game->labelW = tmp->w;
	game->labelH = tmp->h;
	game->label = SDL_CreateTextureFromSurface(game->renderer, tmp);
	SDL_FreeSurface(tmp);
}

void renderGameWonScreen(game_t *game){
	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, MAX-170);

	SDL_RenderClear(game->renderer);

	SDL_SetRenderDrawColor(game->renderer, MAX, MAX, MAX, MAX);

	SDL_Rect textRect = {180, 350- game->labelH, game->labelW, game->labelH};
	SDL_RenderCopy(game->renderer, game->label, NULL, &textRect);
}

void quitGameWonScreen(game_t *game){
	SDL_DestroyTexture(game->label);
	game->label = NULL;
}



//this function isn't written cleanly as it was half-assed 2 days prior to the deadline
//	and the whole idea of a menu is as fresh as a cold melon in a midsummer day.
// but thats why we have comments right ?... for dumb ass code like this.
int menu(game_t *game){

	//init time for the menu only, x & y for position of button press
	int x, y;

	char *menuItem[MENU_NUM] = {"Play", "Exit"};

	SDL_Surface *menus[MENU_NUM];

	//should be a bool for the item that is selected to be true
	int selected[MENU_NUM] = {0,0};

	//								white			red
	SDL_Color colors[MENU_NUM] = {{MAX,MAX,MAX}, {MAX,0,0}};

	menus[0] = TTF_RenderText_Blended(game->font, menuItem[0], colors[0]);
	menus[1] = TTF_RenderText_Blended(game->font, menuItem[1], colors[0]);

	SDL_Texture *label[MENU_NUM];

	SDL_Rect pos[MENU_NUM];

	//centering the labels
	pos[0].x = WINDOW_W/2 - menus[0]->clip_rect.w/2;
	pos[0].y = WINDOW_H/2 - menus[0]->clip_rect.h/2 - 50;
	pos[0].w = menus[0]->clip_rect.w;
	pos[0].h = menus[0]->clip_rect.h;

	pos[1].x = WINDOW_W/2 - menus[1]->clip_rect.w/2;
	pos[1].y = WINDOW_H/2 - menus[1]->clip_rect.h/2 + 50;
	pos[1].w = menus[1]->clip_rect.w;
	pos[1].h = menus[1]->clip_rect.h;

	//the idea is to make a main loop that is specific for the menu
	//	so it will loop until we exit the menu which is what we want
	//	it won't affect the main game loop.

	SDL_Event event;
	// int exitMenu = 0; probably will delete

	while(1){

		//getTicks gets the time in ms so we have to devide for sec.
		// time = SDL_GetTicks() / 1000; 

		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					// game->state = GAME_CLOSED; decided to cancel that out for now
					SDL_FreeSurface(menus[0]);
					SDL_FreeSurface(menus[1]);
					//means menu option 1 is chosen which is "exit" 
					//which is also the same as GAME_CLOSED but i will do both as i have no time for debugging
					return 1;

				case SDL_MOUSEMOTION:
					x = event.motion.x;
					y = event.motion.y;
					//check if x, y inside any menu item
					for(int i=0; i<MENU_NUM; i++){
						//collision detection in a nutshell
						if(x >= pos[i].x && x <= pos[i].x+pos[i].w && y >= pos[i].y && y <= pos[i].y+pos[i].h){
							if(!selected[i]){
								selected[i] = 1;
								SDL_FreeSurface(menus[i]);
								SDL_DestroyTexture(label[i]);
								label[i] = NULL;
								menus[i] = TTF_RenderText_Solid(game->font, menuItem[i], colors[1]);
								label[i] = SDL_CreateTextureFromSurface(game->renderer, menus[i]);
							}
						}
						else{
							if(selected[i]){
								selected[i] = 0;
								SDL_FreeSurface(menus[i]);
								SDL_DestroyTexture(label[i]);
								label[i] = NULL;
								menus[i] = TTF_RenderText_Solid(game->font, menuItem[i], colors[0]);
								label[i] = SDL_CreateTextureFromSurface(game->renderer, menus[i]);
							}
						}
					}
					break;

				case SDL_MOUSEBUTTONDOWN:
					x = event.button.x;
					y = event.button.y;

					//same same but for clicking no hovering
					for(int i=0; i<MENU_NUM; i++){
						//still same but for clicking
						if(x >= pos[i].x && x <= pos[i].x+pos[i].w && y >= pos[i].y && y <= pos[i].y+pos[i].h){
							SDL_FreeSurface(menus[0]);
							SDL_FreeSurface(menus[1]);
							return i;
						}
					}
					break;

				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_ESCAPE){
						return 0;//as in the first element wich is continue
					}
					break;
			}
		}

		//draing ba2a
		SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, MAX);

		SDL_RenderClear(game->renderer);

		SDL_SetRenderDrawColor(game->renderer, MAX, MAX, MAX, MAX);

		SDL_RenderCopy(game->renderer, label[0], NULL, &pos[0]);
		SDL_RenderCopy(game->renderer, label[1], NULL, &pos[1]);

		SDL_RenderPresent(game->renderer);

	}
	return 0; //not sure might hate that return later
}

#endif //SIDESCREEN_H_