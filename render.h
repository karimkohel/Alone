#ifndef RENDER_H_
#define RENDER_H_

void render(game_t *game){

	SDL_SetRenderDrawColor(game->renderer, MAX, MAX, MAX, MAX);

	SDL_RenderClear(game->renderer);

	SDL_RenderPresent(game->renderer);
}


 #endif //RENDER_H
