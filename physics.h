#ifndef PHYSICS_H_
#define PHYSICS_H_

void physics(game_t *game){

	game->time++;

	if(game->time > 120){
        game->state = GAME_RUNNING;
	}

	if(game->state == GAME_RUNNING){

		if(game->boy.dx != 0 && game->boy.onLedge){
			if(game->time%10 == 0){
				if(game->boy.animFrame == 0){
					game->boy.animFrame = 1;
				}
				else{
					game->boy.animFrame = 0;
				}
			}
		}

		game->boy.y += game->boy.dy;
	
		game->boy.dy += GRAVITY;
	
		game->boy.x += game->boy.dx;

		game->scrollX = -game->boy.x+150;

    if(game->scrollX > 0)
      game->scrollX = 0;
	}
	
} 

void detectCollision(game_t *game){
	int mx = game->boy.x, my = game->boy.y; //m for man
	int mw = 100, mh = 140;
	int bx, by, bw, bh; //b for brick

	for(int i=0; i<50; i++){

		bx = game->ledges[i].x;
		bw = game->ledges[i].w;
		by = game->ledges[i].y;
		bh = game->ledges[i].h;

		if(mx < -25){
			game->boy.x = -25;
			mx = 0;
		}

      	if(mx+mw/2 > bx && mx+mw/2<bx+bw){
          
            //are we bumping our head?
            if(my < by+bh && my > by ){
              //correct y
              game->boy.y = by+bh;
              my = by+bh;
              
              //bumped our head, stop any jump velocity
              game->boy.dy = 0;
              game->boy.onLedge = 1;
            }
          }
          if(mx+mw > bx && mx<bx+bw){
            //are we landing on the ledge
            if(my+mh > by && my < by){
              //correct y
              game->boy.y = by-mh;
              my = by-mh;
              
              //landed on this ledge, stop any jump velocity
              game->boy.dy = 0;
              game->boy.onLedge = 1;
            }
          }
        
          if(my+mh > by && my<by+bh){
            //rubbing against right edge
            if(mx < bx+bw && mx+mw > bx+bw){
              //correct x
              game->boy.x = bx+bw;
              mx = bx+bw;
              
              game->boy.dx = 0;
            }
            //rubbing against left edge
            else if(mx+mw > bx && mx < bx){
              //correct x
              game->boy.x = bx-mw;
              mx = bx-mw;
              
              game->boy.dx = 0;
            }
          }

	}
}

#endif //PHYSICS_H_