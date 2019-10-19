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
void MakeFloor(tile* tiles[500][500], int width, int height, int screen_x_offset, int screen_y_offset, int floorcount){
  int i, j, xdoor = 0, ydoor = 0;
  int iLimit = 100 + ((floorcount-1)*width); //increases based on the floor you are on
  int jLimit = 100 + ((floorcount - 1)*height);
	for(i = 0; i < iLimit; i++){ 
	  for(j = 0; j < jLimit; j++){ //the two for loops will change limits based on the floor count acessing and making the floor bigger as the player goes to higher floors
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
	tiles[rand()%iLimit][rand()%jLimit]->stair = 1;
	floorcount++; //took out limit on floors so there is now infinte floors, atleast until the game runs out of memory
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

	tile * tiles[500][500];  //tiles that represent the floor
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
	
	int health = 100; //Variable to Keep Track of Health

	int score = 0;
	
	int floorcount = 1;

	int save = 1;

	char str[90];

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

		  mvprintw(screen_y_offset - 3, screen_x_offset + 18, "The Health is: %d  ", health);//prints out health one line above the score

		  if(move_counter > move_timeout) {
		    userIn = read_escape(&arrow);

		    if(userIn == REGCHAR){ //Checks that input is a regular character
		      if(arrow == 'p' || arrow == 'P'){ //If P enter the While loop to pause
			char* options[5] = {"Resume", "Save", "Load Game", "Help Menu", "Quit Game"};
			int count = 0;
		       
			while(1){
			
			  userIn = read_escape(&arrow); //Resets to keep in while loop and read input

			  if(userIn == UP){ //updates count to keep track of where cursor is in pause menu
			    count --; 
			    if(count < 0){
			      count = 4;
			    }
			  }

			  if(userIn == DOWN){ //does same as above but for pressing down arrow
			    count ++;
			    if(count > 4){
			      count = 0;
			    }
			  }

			  if(userIn == REGCHAR){


			    if(arrow == 10){
			      if(count == 0){
				break;}
			      if(count == 1){
				FILE *file_pointer; //creates file pointer
				sprintf(str, "saves/save_%d.game", save); //creates the format to save the program as
				file_pointer = fopen(str, "w"); //sets the file_pointer
				int i,j;
				for(i = 0; i < width-1; i++){
				  for(j = 0; j < height-1; j++){
				    char saveCell;
				    sprintf(&saveCell, "%d\n", tiles[i][j]->state[CURRENT]); //saves all the tiles in thegame
				    fputs(&saveCell, file_pointer);}//puts all the tiles into the file_pinter
				}

				fclose(file_pointer);
				save++;//sets up file for next save
			      }
			      if(count == 2){
				while(1){
				  nodelay(stdscr, FALSE); //dont wait for input
				  echo();
				
				  mvprintw(9, screen_x_offset - 13, "Which Save would you like to load, there is a maximum of 10:");
				  mvprintw(9, screen_x_offset + 47, " "); //prompt which save they player wants to load
				  scanw("%d", &userIn); //scans what load the player wants

				  nodelay(stdscr, TRUE); //wait for input
				  noecho();

				  if(userIn >= 1 && userIn <= 10){
				    break; 
				  }
				  mvprintw(10, screen_x_offset - 18, "Invalid save number please choose from 1 to 10"); //if the sae number is not between 1 and ten tell them thsi
				}
				mvprintw(9, screen_x_offset - 18, "                                                                         ");
				mvprintw(10, screen_x_offset + 7, "     ");
				char loading[10];
				sprintf(loading, "saves/save_%d.game", userIn); //get the save data and put it into a char array
				FILE *load_pointer;
				
				load_pointer = fopen(loading, "r"); //open the data
				if(load_pointer == NULL){
				  mvprintw(9, screen_x_offset - 13, "%s does not exist.", loading); //if data doesn't exist, i.e. the save doesnt exist return this to prevent crash
				  break;
				}

				int i, j, value;
				for(i = 0; i < width - 1; i++){
				  for(j = 0; j < height -1; j++){
				    fscanf(load_pointer, "%d", &value); //load the pointer and get the vlaue from the file
				    if(value == 0){
				      tiles[i][j]->state[CURRENT] = PLAYER; //if the value is 0 it is the player
				      player->x = i; //set the player to that location
				      player->y = j;
				    }
				    else if(value == 1){
                                      tiles[i][j]->state[CURRENT] = LOOT; //if 1 then it is loot
                                    }
				    else if(value == 2){
                                      tiles[i][j]->state[CURRENT] = EMPTY; //if 2 then it is empty
                                    }
				    else if(value == 3){
                                      tiles[i][j]->state[CURRENT] = ENEMY; //if 3 it is a normal enemy
                                    }
				    else if(value == 4){
                                      tiles[i][j]->state[CURRENT] = UNCHANGED; //if 4 it is unchanged
                                    }
				    else if(value == 5){
                                      tiles[i][j]->state[CURRENT] = STRONGENEMY; //if it is 5 it is a strong enemy
                                    }
				    else{ 
                                      tiles[i][j]->state[CURRENT] = BOSSENEMY; //if it is 6 then it is a boss enemy
                                    }
				  }
				}
			      }
			      if(count == 3){
				erase(); //clear screen for help menu
				int remove = 1;
				while(remove){
				  userIn = read_escape(&remove); //read input from user
				  mvprintw(5, screen_x_offset - 18, "Press Up arrow to move up"); //display different keybinds
				  mvprintw(6, screen_x_offset - 18, "Press Down arrow to move down");
				  mvprintw(7, screen_x_offset - 18, "Press Left Arrow to move Left");
				  mvprintw(8, screen_x_offset - 18, "Press Right Arrow to move Right");
                                  mvprintw(9, screen_x_offset - 18, "Press S to save the game");
				  mvprintw(10, screen_x_offset - 18, "Press L to load a game");
				  mvprintw(11, screen_x_offset - 18, "Press P to Pause the game");
                                  mvprintw(12, screen_x_offset - 18, "Press Q to quit the game");
				  mvprintw(13, screen_x_offset - 18, "Press any letter key to exit this menu");
				  if(userIn == REGCHAR) remove = 0; //once the user inputs a key it returns 0 so remove is 0 and the help menu is exited
				}
				erase();
				break;
			      }
			      if(count == 4){
				state = EXIT; //change state to exit when selected
				break;
			      }
			    }			  

			  if(userIn == REGCHAR && (arrow == 'p' || arrow == 'P')){ //When input is P again unpause
			    break;}
			  }
			  int i = 0;
			  for(i = 0; i < 5; i++){
			    if(i == count){
			      init_pair(1, COLOR_BLACK, COLOR_RED); //sets selected item on pause menu to this color
			      attron(COLOR_PAIR(1));
			      mvprintw(25 + i, 1, "%s", options[i]); //prints the entry from the different option choices
			      attroff(COLOR_PAIR(1));
			    }
			    else{
			      init_pair(2, COLOR_BLACK, COLOR_BLUE); //rest of pause meneu is this color
			      attron(COLOR_PAIR(2));
			      mvprintw(25+i, 1, "%s", options[i]);
			      attroff(COLOR_PAIR(2));
			    }
			  }

			}
			mvprintw(25, 1, "                                     ");
                        mvprintw(26, 1, "                                     ");
                        mvprintw(27, 1, "                                     ");
                        mvprintw(28, 1, "                                     ");
                        mvprintw(29, 1, "                                     ");
                        mvprintw(30, 1, "                                     ");
                        mvprintw(31, 1, "                                     ");
                        mvprintw(32, 1, "                                     ");
                        mvprintw(33, 1, "                                     ");

		      }
		      if(arrow == 'q' || arrow == 'Q'){
			state = EXIT;}
		      if(arrow == 's' || arrow == 'S'){
			FILE *file_pointer; //creates file pointer
			sprintf(str, "saves/save_%d.game", save); //creates the format to save the program as
			file_pointer = fopen(str, "w"); //sets the file_pointer
			int i,j;
			for(i = 0; i < width-1; i++){
			  for(j = 0; j < height-1; j++){
			    char saveCell;
			    sprintf(&saveCell, "%d\n", tiles[i][j]->state[CURRENT]); //saves all the tiles in thegame 
			    fputs(&saveCell, file_pointer);}//puts all the tiles into the file_pinter
			}
			
			fclose(file_pointer);
			save++;//sets up file for next save
		      }

		      if(arrow == 'l' || arrow == 'L'){
			while(1){
			  nodelay(stdscr, FALSE); //dont wait for input
			  echo();

			  mvprintw(9, screen_x_offset - 13, "Which Save would you like to load, there is a maximum of 10:");
			  mvprintw(9, screen_x_offset + 47, " "); //prompt which save they player wants to load
			  scanw("%d", &userIn); //scans what load the player wants

			  nodelay(stdscr, TRUE); //wait for input
			  noecho();

			  if(userIn >= 1 && userIn <= 10){
			    break;
			  }
			  mvprintw(10, screen_x_offset - 18, "Invalid save number please choose from 1 to 10"); //if the sae number is not between 1 and ten tell them thsi
			}
			mvprintw(9, screen_x_offset - 18, "                                                                         ");
			mvprintw(10, screen_x_offset + 7, "     ");
			char loading[10];
			sprintf(loading, "saves/save_%d.game", userIn); //get the save data and put it into a char array
			FILE *load_pointer;

			load_pointer = fopen(loading, "r"); //open the data
			if(load_pointer == NULL){
			  mvprintw(9, screen_x_offset - 13, "%s does not exist.", loading); //if data doesn't exist, i.e. the save doesnt exist return this to prevent crash
			  break;
			}

			int i, j, value;
			for(i = 0; i < width - 1; i++){
			  for(j = 0; j < height -1; j++){
			    fscanf(load_pointer, "%d", &value); //load the pointer and get the vlaue from the file
			    if(value == 0){
			      tiles[i][j]->state[CURRENT] = PLAYER; //if the value is 0 it is the player
			      player->x = i; //set the player to that location
			      player->y = j;
			    }
			    else if(value == 1){
			      tiles[i][j]->state[CURRENT] = LOOT; //if 1 then it is loot
			    }
			    else if(value == 2){
			      tiles[i][j]->state[CURRENT] = EMPTY; //if 2 then it is empty
			    }
			    else if(value == 3){
			      tiles[i][j]->state[CURRENT] = ENEMY; //if 3 it is a normal enemy
			    }
			    else if(value == 4){
			      tiles[i][j]->state[CURRENT] = UNCHANGED; //if 4 it is unchanged
			    }
			    else if(value == 5){
			      tiles[i][j]->state[CURRENT] = STRONGENEMY; //if it is 5 it is a strong enemy
			    }
			    else{
			      tiles[i][j]->state[CURRENT] = BOSSENEMY; //if it is 6 then it is a boss enemy
			    }
			  }
			}
		      }	  
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
				  health -= 25; //if the regular enemy hits the player deduct 25 health

				if(move_strongenemies(player, x_offset, y_offset, width, height, tiles)){ //moves strong enemies by calling function in tiles.c
				  health -= 50;} //if one of the strong enemies hits the player deduct 50 health

				if(move_bossenemies(player, x_offset, y_offset, width, height, tiles)){ //moves boss enemies by calling function in tiles.c
				  health -= 100;} //if one of the bosses hits the player deduct 100 health

				if(health <= 0){
				  state = EXIT;} //if the health goes below 0 the game is over

				draw_room(r);
				update_tiles(x_offset, y_offset, width, height, tiles);
				display_tiles(x_offset, y_offset, width, height, tiles);
				
				while(getch() != ERR);  //prevents lag from having getch and sleep in a loop

				move_counter = 0;
			}
			move_counter++;
			break;
		case EXIT:
		  erase(); //clears screen
		  mvprintw(screen_y_offset, screen_x_offset, "The game is over your score is: %d", score); //displays score
		  mvprintw(screen_y_offset + 1, screen_x_offset, "Press any letter key to end the game"); //prompts for key
		  while(1){
		    userIn = read_escape(&arrow); //reads key
		    if(userIn == REGCHAR){//once key is entered end game
		      break;}
		  }
		  
			endwin();
			return(0);
			break;
		}
		refresh();
		nanosleep(&tim,&tim_ret);
	}
}

