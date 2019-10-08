/* game.c ---------
 *
 * Filename: game.c
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
 */

/* Copyright (c) 2018 The Trustees of Indiana University and
 * Indiana University Research and Technology Corporation.
 *
 * All rights reserved.
 *
 * Additional copyrights may follow
 */

#include <unistd.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "tile.h"
#include "game.h"
#include "room.h"
#include "key.h"


//function the fill the array with tiles to make a floor
void MakeFloor(tile* tiles[100][100], int width, int height, int screen_x_offset, int screen_y_offset, int floorcount){
  int i, j, xdoor = 0, ydoor = 0;
	for(i = 0; i < 100; i++){
		for(j = 0; j < 100; j++){
		  tiles[i][j] = create_tile(i, j, screen_x_offset + i%width, screen_y_offset + j%height, 0, 0, 0);
		  if(xdoor == 0){ //if the count of doors on a given x line is 0 then try and place a door
		    if(j%height == 0 && j != 0 && rand()%height == 1){
	       		tiles[i][j]->door = 1;
       			tiles[i][j-1]->door = 1;
			xdoor = 1;} //set equal to 1 when door is placed
		  }
		  if(ydoor == 0){ //if the count of doors on a given y line is 0 then try and place a door
		    if(i%width == 0 && i != 0 && rand()%width == 1){
       			tiles[i][j]->door = 1;
			tiles[i-1][j]->door = 1;
			ydoor = 1; //set equal to 1 when door is placed
		    }
		  }
		  if(i%width == 0){ //when the middle line is reached then change xdoor back to 0
                    xdoor = 0;}
		  if(j%height == 0){ //when the height is reached reset to get ydoor back to zero
		    ydoor = 0;}
		}

	}
	if(floorcount <= 4){ //keep track of the floors created and don't create more stairs when 4 is passed
	  tiles[rand()%100][rand()%100]->stair = 1;
	  floorcount++;}
	tiles[width/2][height/2]->state[CURRENT] = PLAYER;
}

void init_game(void)
{
	int x,y;
}

int game(void)
{
	srand(time(0));  //Seed random numbers

	static int state = INIT;
	struct timespec tim = {0,1000000};  // Each execution of while(1) is approximately 1mS
	struct timespec tim_ret;

	int width = 50;
	int height = 25;

	tile * tiles[100][100];  //tiles that represent the floor
	tile * player;           //pointer to keep track of the player

	room_t *r;

	int x_offset=0, y_offset=0;
	int screen_x_offset, screen_y_offset;
	int x_max, y_max;
	int arrow;
	int move_counter = 0;
	int move_timeout = BASE_TIMEOUT/10;

	int test = 0;

	int userIn;

	int score = 0;
	
	int floorcount = 1;

	while(1) {
		switch(state) {
		case INIT:                   // Initialize the game, only run one time


			initscr();
			nodelay(stdscr, TRUE);   // Do not wait for characters using getch.
			noecho();                // Do not echo input characters
			getmaxyx(stdscr, y_max, x_max);  // Get the screen dimensions
			
			curs_set(0);

			screen_x_offset = (x_max / 2) - ((width) / 2);
			screen_y_offset = (y_max / 2) - ((height) / 2);

			MakeFloor(tiles, width, height, screen_x_offset, screen_y_offset, floorcount);

			tiles[width/2][height/2]->state[CURRENT] = PLAYER;
			player = tiles[width/2][height/2];


			r = init_room(screen_x_offset - 1, screen_y_offset - 1, width+1, height+1);
			draw_room(r);

			state = STEP;
			break;
		case STEP:

		  mvprintw(screen_y_offset - 2, screen_x_offset + 18, "The Score is: %d", score);//score counter prints on the top middle of screen

		  if(move_counter > move_timeout) {
		    userIn = read_escape(&arrow);

		    if(userIn == REGCHAR){ //Checks that input is a regular character
		      if(arrow == 'p' || arrow == 'P'){ //If P enter the While loop to pause
			while(1){
			  userIn = read_escape(&arrow); //Resets to keep in while loop and read input
			  if(userIn == REGCHAR && (arrow == 'p' || arrow == 'P')){ //When input is P again unpause
			    break;}
			}
		      }
		      if(arrow == 'q' || arrow == 'Q'){
			state = EXIT;}
		    }

		    if(userIn == UP){
		      test = move_player(&player, player->x, (player->y) - 1, width, height, tiles);
		      if(test == 1){ //if move player returned one you are on gold so increase score
			score += 1;}
		      if(test == 5){ //if 5 is returned from move player you are on a door
			player->state[NEW] = EMPTY; //reset state
			player = tiles[player->x][player->y - 1]; //move player accordingly
			player->state[NEW] = PLAYER; //Set state at new location to player
			y_offset -= height;} //Change offset window
		      if(test == 6){
			MakeFloor(tiles, width, height, screen_x_offset, screen_y_offset, floorcount); //if 6 is returned then you are on a stair and a new floor is made
		      }
		    }
		    if(userIn == DOWN){
			test = move_player(&player, player->x, (player->y) + 1, width, height, tiles);
			if(test == 1){
			  score += 1;}
			if(test == 5){
			  player->state[NEW] = EMPTY;
			  player = tiles[player->x][player->y + 1];
			  y_offset += height;
			}
			if(test == 6){
			  MakeFloor(tiles, width, height, screen_x_offset, screen_y_offset, floorcount);
			}
		      }
		      if(userIn == RIGHT){
			test = move_player(&player, (player->x) + 1, player->y, width, height, tiles);
			if(test == 1){
			  score += 1;}
			if(test == 5){
			  player->state[NEW] = EMPTY;
			  player = tiles[player->x + 1][player->y];
			  x_offset += width;}
			if(test == 6){
			  MakeFloor(tiles, width, height, screen_x_offset, screen_y_offset, floorcount);
			}
		      }
		      if(userIn == LEFT){
			test = move_player(&player, (player->x) - 1, player->y, width, height, tiles);
			if(test == 1){
			  score += 1;}
			if(test == 5){
			  player->state[NEW] = EMPTY;
			  player = tiles[player->x -1][player->y];
			  x_offset -= width;}
			if(test == 6){
			  MakeFloor(tiles, width, height, screen_x_offset, screen_y_offset, floorcount);
			}
		      }

				

				
				if(move_enemies(player, x_offset, y_offset, width, height, tiles))
					state = EXIT;

				draw_room(r);
				update_tiles(x_offset, y_offset, width, height, tiles);
				display_tiles(x_offset, y_offset, width, height, tiles);
				
				while(getch() != ERR);  //prevents lag from having getch and sleep in a loop

				move_counter = 0;
			}
			move_counter++;
			break;
		case PAUSE:
		  printf("This is the Pause State, press P again to keep playing");
		  state = STEP;
		case EXIT:
			endwin();
			return(0);
			break;
		}
		refresh();
		nanosleep(&tim,&tim_ret);
	}
}
