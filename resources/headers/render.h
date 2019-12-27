#ifndef RENDER_H_
#define RENDER_H_

void renderGame(game_t *game){

	SDL_SetRenderDrawColor(game->renderer, MAX, MAX, MAX, MAX);
	SDL_RenderClear(game->renderer);

	//background
	SDL_Rect mapRect = {0, 0, WINDOW_W, WINDOW_H};
	SDL_RenderCopy(game->renderer, game->mapText, NULL, &mapRect);

	//ledges
	for(int i=0; i<100; ++i){
		SDL_Rect ledgeRect = {game->scrollX+game->ledges[i].x, game->ledges[i].y, game->ledges[i].w, game->ledges[i].h};
		SDL_RenderCopy(game->renderer, game->brick, NULL, &ledgeRect);
	}

	//ghosts
	for(int i=0; i<50; ++i){
		SDL_Rect ghostRect = {game->scrollX+game->ghost[i].x, game->ghost[i].y, game->ghost[i].w, game->ghost[i].h};
		SDL_RenderCopy(game->renderer, game->ghostText, NULL, &ghostRect);
	}


	//boy
	SDL_Rect boyRect = {game->scrollX+game->boy.x, game->boy.y, 100, 140};
	SDL_RenderCopyEx(game->renderer, 
		game->boyText[game->boy.animFrame], 
		NULL, &boyRect, 0, NULL, 
		(game->boy.faceLeft != 0));
}

void render(game_t *game){

	if(game->state == GAME_INIT){
		renderLivesScreen(game);
	}
	else if(game->state == GAME_RUNNING){
		renderGame(game);
	}
	else if(game->boy.isDead && game->state == GAME_OVER){
		renderGameOver(game);
	}

	SDL_RenderPresent(game->renderer);

	SDL_Delay(1);
}

 #endif //RENDER_H