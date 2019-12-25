#ifndef RENDER_H_
#define RENDER_H_

void render(game_t *game){

	SDL_SetRenderDrawColor(game->renderer, MAX, MAX, MAX, MAX);
	SDL_RenderClear(game->renderer);

	//background
	SDL_Rect mapRect = {0, 0, WINDOW_W, WINDOW_H};
	SDL_RenderCopy(game->renderer, game->mapText, NULL, &mapRect);

	//ledges
	for(int i=0; i<100; ++i){
		SDL_Rect ledgeRect = {game->ledges[i].x, game->ledges[i].y, game->ledges[i].w, game->ledges[i].h};
		SDL_RenderCopy(game->renderer, game->brick, NULL, &ledgeRect);
	}

	//boy
	SDL_Rect boyRect = {game->boy.x, game->boy.y, 100, 140};
	SDL_RenderCopyEx(game->renderer, game->boyText[0], NULL, &boyRect, 0, NULL, 0);




	SDL_RenderPresent(game->renderer);

	SDL_Delay(10);

}


 #endif //RENDER_H
