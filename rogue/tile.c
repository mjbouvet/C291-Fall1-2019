/* tile.c ---------
 *
 * Filename: cell.c
 * Description:
 * Author: Dmitrii Galantsev
 * Maintainer:
 * Created:      May 12 11:28 2018
 * Last-Updated: June 4 11:00 2019
 *           By: Matthew Fulford
 */

/* Commentary:
 *
 *
 *
 */

/* Copyright (c) 2018 The Trustees of Indiana University and
 * Indiana University Research and Technology Corporation.
 *
 * All rights reserved.
 *
 * Additional copyrights may follow
 */

/* Code: */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <ncurses.h>
#include "tile.h"

tile * create_tile(int init_x, int init_y, int d_x, int d_y, int p, int l, int e)
{

    // create the tile
    tile * t = malloc(sizeof(tile));
    t->x = init_x;
    t->y = init_y;
	
    t->draw_x = d_x;
    t->draw_y = d_y;

    t->door = 0;
    t->stair = 0;

    if(p){
    	t->state[CURRENT] = PLAYER;
    }else if(l){
	t->state[CURRENT] = LOOT;
    }else if(e){
	t->state[CURRENT] = EMPTY;
    }else if(rand()%100 == 1){
	t->state[CURRENT] = LOOT;
    }else if(rand()%500 == 1){
	t->state[CURRENT] = ENEMY;
    }else if(rand()%1000 == 1){
      t->state[CURRENT] = STRONGENEMY;
    }else if(rand()%2500 == 1){
      t->state[CURRENT] = BOSSENEMY;
    }else{
	t->state[CURRENT] = EMPTY;
    }
    t->state[NEW] = UNCHANGED;

    return(t);
}

int destroy_tile (tile * t)
{
    free(t);

    return SUCCESS;
}

int update_tile (tile * t){
	if(t->state[NEW] != UNCHANGED){
    		t->state[OLD] = t->state[CURRENT];
    		t->state[CURRENT] = t->state[NEW];
    		t->state[NEW] = UNCHANGED;
	}

	return SUCCESS;
}

void update_tiles(int x_off, int y_off, int x, int y, tile* t[100][100]){
	int i, j;
	for(i=0;i<x;i++)
		for(j=0;j<y;j++)
			update_tile(t[i+x_off][j+y_off]);
}

void display_tile (tile * t)
{
	if (t->state[CURRENT] == PLAYER){
		mvprintw(t->draw_y, t->draw_x, "@");
	}else if(t->state[CURRENT] == LOOT){
		mvprintw(t->draw_y, t->draw_x, "$");
	}else if(t->state[CURRENT] == ENEMY){
		mvprintw(t->draw_y, t->draw_x, "E");
	}else if(t->state[CURRENT] == STRONGENEMY){
	        mvprintw(t->draw_y, t->draw_x, "X");
	}else if(t->state[CURRENT] == BOSSENEMY){
	  mvprintw(t->draw_y, t->draw_x, "B");
	}else if(t->door){
		mvprintw(t->draw_y, t->draw_x, "D");
	}else if(t->stair){
		mvprintw(t->draw_y, t->draw_x, "H");
	}else{
		mvprintw(t->draw_y, t->draw_x, " ");
	}
}


void display_tiles (int x_off, int y_off, int width, int height, tile * t[100][100])
{
    int x, y;
	for (x = 0; x < width; x++)
		for (y = 0; y < height; y++)
			display_tile(t[x+x_off][y+y_off]);
}

//function for moving all the enemies
int move_enemies(tile* player, int x_off, int y_off, int x, int y, tile* t[100][100]){
        static count;

        if(count != 5){
                count++;
                return 0;
        }

        int i, j;
        for(i=0;i<x;i++)
                for(j=0;j<y;j++){
                        if(t[i+x_off][j+y_off]->state[CURRENT] == ENEMY){
                                int x_diff = abs(player->x - (i+x_off));
                                int y_diff = abs(player->y - (j+y_off));

                                if(x_diff == 0 && y_diff == 0){
                                        t[i+x_off][j+y_off]->state[CURRENT] = PLAYER;
                                        return 1;
                                }else if(x_diff > y_diff){
                                        int new_x = i+x_off + (player->x - (i+x_off))/x_diff;
                                        t[i+x_off][j+y_off]->state[NEW] = EMPTY;
                                        t[new_x][j+y_off]->state[NEW] = ENEMY;
                                }else{
                                        int new_y = j+y_off + (player->y - (j+y_off))/y_diff;
                                        t[i+x_off][j+y_off]->state[NEW] = EMPTY;
                                        t[i+x_off][new_y]->state[NEW] = ENEMY;
                                }
                        }
                }
        count = 0;
        return 0;
}


int move_strongenemies(tile* player, int x_off, int y_off, int x, int y, tile* t[100][100]){
  static count;

  if(count != 10){
    count++;
    return 0;
  }

  int i, j;
  for(i=0;i<x;i++)
    for(j=0;j<y;j++){
      if(t[i+x_off][j+y_off]->state[CURRENT] == STRONGENEMY){
	int x_diff = abs(player->x - (i+x_off));
	int y_diff = abs(player->y - (j+y_off));

	if(x_diff == 0 && y_diff == 0){
	  t[i+x_off][j+y_off]->state[CURRENT] = PLAYER;
	  return 1;
	}else if(x_diff > y_diff){
	  int new_x = i+x_off + (player->x - (i+x_off))/x_diff;
	  t[i+x_off][j+y_off]->state[NEW] = EMPTY;
	  t[new_x][j+y_off]->state[NEW] = STRONGENEMY;
	}else{
	  int new_y = j+y_off + (player->y - (j+y_off))/y_diff;
	  t[i+x_off][j+y_off]->state[NEW] = EMPTY;
	  t[i+x_off][new_y]->state[NEW] = STRONGENEMY;
	}
      }
    }
  count = 0;
  return 0;
}

int move_bossenemies(tile* player, int x_off, int y_off, int x, int y, tile* t[100][100]){
  static count;

  if(count != 20){
    count++;
    return 0;
  }

  int i, j;
  for(i=0;i<x;i++)
    for(j=0;j<y;j++){
      if(t[i+x_off][j+y_off]->state[CURRENT] == BOSSENEMY){
        int x_diff = abs(player->x - (i+x_off));
        int y_diff = abs(player->y - (j+y_off));

        if(x_diff == 0 && y_diff == 0){
          t[i+x_off][j+y_off]->state[CURRENT] = PLAYER;
          return 1;
        }else if(x_diff > y_diff){
          int new_x = i+x_off + (player->x - (i+x_off))/x_diff;
          t[i+x_off][j+y_off]->state[NEW] = EMPTY;
          t[new_x][j+y_off]->state[NEW] = BOSSENEMY;
        }else{
          int new_y = j+y_off + (player->y - (j+y_off))/y_diff;
          t[i+x_off][j+y_off]->state[NEW] = EMPTY;
          t[i+x_off][new_y]->state[NEW] = BOSSENEMY;
        }
      }
    }
  count = 0;
  return 0;
}


//A function for moving the player
int move_player (tile** player, int new_x, int new_y, int width, int height, tile * t[100][100])
{	
	int down,up,left,right;

	//decide enemie's direction of movement
	if(new_x >= 0 && new_x < (*player)->x && new_x%width < (*player)->x%width)
	 	down = 1;
	else 
		down=0;
	if(new_x >= 0 && new_x > (*player)->x && new_x%width > (*player)->x%width)
		up=1;
	else up=0;
	if(new_y >= 0 && new_y < (*player)->y && new_y%height < (*player)->y%height)
	  left =1;
	else 
		left =0;
	if(new_y >= 0 && new_y > (*player)->y && new_y%height > (*player)->y%height)
		right=1;
	else
		right=0;

	if(down || up || left || right){
		if(t[new_x][new_y]->state[CURRENT] == LOOT){
			t[new_x][new_y]->state[NEW] = PLAYER;
			t[(*player)->x][(*player)->y]->state[NEW] = EMPTY;

			*player = t[new_x][new_y];
			return 1;    //returns 1 whe nthe player picks up gold
		}else if(t[new_x][new_y]->state[CURRENT] == ENEMY){
			t[new_x][new_y]->state[NEW] = PLAYER;
			t[(*player)->x][(*player)->y]->state[NEW] = EMPTY;

			*player = t[new_x][new_y];
			return -1;    //returns -1 when the player walks into a monster
		}else if(t[new_x][new_y]->stair){
		  if(t[new_x][new_y]->stair){
		    return 6;}} //If your tile is a stair return 6
		else{
			t[new_x][new_y]->state[NEW] = PLAYER;
			t[(*player)->x][(*player)->y]->state[NEW] = EMPTY;

			*player = t[new_x][new_y];
			return 2;    //returns 2 when the player walks into an empty tile
		}
	}else{
	  if(t[new_x][new_y]->door){
	    return 5;} //you can't move forward and your space is a door, so return 5 to be used in game.c
	  return 0;    //returns 0 if the player isn't allowed to move
	}
}
