#ifndef GAME_H_
#define GAME_H_

#define WINDOW_W 650
#define WINDOW_H 550

#define MAX 255
#define GAME_INIT 0
#define GAME_RUNNING 1
#define GAME_OVER 2
#define GAME_CLOSED 3

typedef struct{
	
} man_t ;

typedef struct{

	//rendering
	SDL_Window *window;
	SDL_Renderer *renderer;

	//textures

	//states
	int state;

	//gamestuff
	double time;
	
} game_t ;



#endif //GAME_H_