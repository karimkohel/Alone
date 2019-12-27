#ifndef GAME_H_
#define GAME_H_

//magic numbers
#define WINDOW_W 950
#define WINDOW_H 650

#define GRAVITY 0.30f

#define MAX 255
#define GAME_INIT 0
#define GAME_RUNNING 1
#define GAME_OVER 2
#define GAME_CLOSED 3

#define LEDGESNUM 100
#define GHOSTNUM 50

//structs
typedef struct{

	int x,y;
	float dx,dy;
	short animFrame;
	short onLedge;
	short faceLeft;
	short isDead;
	short lives;
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
	SDL_Texture *ghostText;

	//font
	TTF_Font *font;
	SDL_Texture *label;
	int labelW;
	int labelH;

	//sounds
	int bgChannel;
	int dieChannel;
	int thunderChannel;
	int walkingChannel;
	Mix_Chunk *bgMusic;
	Mix_Chunk *thunderSound;
	Mix_Chunk *dieSound;
	Mix_Chunk *walkingSound;

	//rects
	ledges_t ledges[LEDGESNUM];
	ledges_t ghost[GHOSTNUM];

	//states
	int state;

	//gamestuff
	int time; // the longest its gonna run is 12 hours max
	int deathCountDown;
	int sideTime;
	int scrollX;
}game_t;

#endif //GAME_H_