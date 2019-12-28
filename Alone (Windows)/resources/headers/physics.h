#ifndef PHYSICS_H_
#define PHYSICS_H_

int collides(int x1,int y1,int x2,int y2,int w1,int h1,int w2,int h2){

  return ( !( ( x1 > (x2+w2)) || (x2 > (x1+w1)) || (y1 > (y2+h2)) || (y2 > (y1+h1)) ) );
}

void process(game_t *game){

	game->time++;

	if(game->time > 120 && game->state != GAME_CLOSED && !game->boy.isDead && !game->boy.win){
        game->state = GAME_RUNNING;
        quitLivesScreen(game);
        game->bgChannel = Mix_PlayChannel(-1, game->bgMusic, -1);
	}

    if(game->boy.win && game->winCountDown < 0){
        game->winCount++;
        initGameWonScreen(game);
        game->state = GAME_WON;
        game->winCountDown = 120;
        Mix_HaltChannel(game->bgChannel);
        Mix_PlayChannel(-1, game->portalSound, 0);
    }
    else if(game->winCountDown >= 0){
        game->winCountDown--;
        if(game->winCountDown <= 0){
            resetGameWon(game);
        }
    }

	if(!game->boy.isDead){

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
	
    if(game->boy.isDead && game->deathCountDown < 0){
        game->deathCountDown = 120;
        Mix_HaltChannel(game->bgChannel);
        Mix_PlayChannel(-1, game->dieSound, 0);
    }
    else if(game->deathCountDown > 0){

        game->deathCountDown--;

        if(game->deathCountDown <= 0){
            
            game->boy.lives--;

            if(game->boy.lives >= 0){
                resetGameLost(game);
            }
            else{
                initGameOver(game);
                game->state = GAME_OVER;
            }

        }
    }
} 

void detectCollision(game_t *game){ //or dropping down ya3ny
	int mx = game->boy.x, my = game->boy.y; //m for man
	int mw = 50, mh = 123;
	int bx, by, bw, bh; //b for brick

    //die if you go off screen
    if(my > WINDOW_H){
        game->boy.isDead = 1;
    }   


    //collision with ghosts
    for(int i=0; i < GHOSTNUM; i++){
        int ghostCollision = collides(mx, my, game->ghost[i].x, game->ghost[i].y, mw, mh, 40, 90);

        if(ghostCollision){
            game->boy.isDead = 1;
        }
    }

    int portalCollide = collides(mx, my, game->portal.x, game->portal.y, mw, mh, 100, 120);
    if(portalCollide){
        game->boy.win = 1;
    }

    //collision with bricks
	for(int i=0; i<LEDGESNUM; i++){

		bx = game->ledges[i].x;
		bw = game->ledges[i].w-30;
		by = game->ledges[i].y;
		bh = game->ledges[i].h;

        //dont exit screen from left
		if(mx < -25){
			game->boy.x = -25;
			mx = -25;
		}

  	if(mx+mw/2 > bx && mx+mw/2<bx+bw){
      
        //are we bumping our head?
        if(my < by+bh && my > by && game->boy.dy < 0){
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
        if(my+mh > by && my < by && game->boy.dy > 0){
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