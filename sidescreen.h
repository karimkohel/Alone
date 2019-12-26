#ifndef SIDESCREEN_H_
#define SIDESCREEN_H_


void initSideScreen(game_t *game){

	char str[30] = "";

	sprintf(str, "You have %d lives left", game->boy.lives);

	SDL_Color white = {MAX, MAX, MAX, MAX};

	SDL_Surface *tmp = TTF_RenderText_Blended(game->font, str, white);
	game->labelW = tmp->w;
	game->labelH = tmp->h;
	game->label = SDL_CreateTextureFromSurface(game->renderer, tmp);
	SDL_FreeSurface(tmp);

}

void renderSideScreen(game_t *game){

	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, MAX-70);//try making it semi transparant

	SDL_RenderClear(game->renderer);

	SDL_SetRenderDrawColor(game->renderer, MAX, MAX, MAX, MAX);

	SDL_Rect textRect = {220, 350- game->labelH, game->labelW, game->labelH};
	SDL_RenderCopy(game->renderer, game->label, NULL, &textRect);

}

void quitSideScreen(game_t *game){

	SDL_DestroyTexture(game->label);
	game->label = NULL;


}

#endif //SIDESCREEN_H_