#ifndef GAME_H_
#define GAME_H_

#define WINDOW_W 950
#define WINDOW_H 650

#define GRAVITY 0.30f

#define MAX 255
#define GAME_INIT 0
#define GAME_RUNNING 1
#define GAME_OVER 2
#define GAME_CLOSED 3

typedef struct{

	int x,y;
	int dx,dy;
	int animFrame;
	int onLedge;
	int faceLeft;
}man_t;

typedef struct{

	int x,y,w,h;
}ledges_t;

typedef struct{

	man_t boy;

	//rendering
	SDL_Window *window;
	SDL_Renderer *renderer;

	//textures
	SDL_Texture *mapText;
	SDL_Texture *brick;
	SDL_Texture *boyText[2];

	//rects
	ledges_t ledges[50];

	//states
	int state;

	//gamestuff
	int time;
	int scrollX;
}game_t;

#endif //GAME_H_