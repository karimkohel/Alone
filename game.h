#ifndef GAME_H_
#define GAME_H_

#define MAX 255
#define GAME_INIT 0
#define GAME_RUNNING 1
#define GAME_OVER 2

typedef struct{
	
} man_t ;

typedef struct{

	//rendering
	SDL_Window *window;
	SDL_Renderer *renderer;

	//textures

	//states
	int gamestate;
	
} game_t ;



#endif //GAME_H_