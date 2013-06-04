#include "gamestate.h"
#include <stdlib.h>

Game* current_game;
Keyboardstate* keyboardstate;


int game_ongoing = 0;
int NUMBER_OF_PLAYERS = 2;
int NUMBER_OF_UNITS = 2;

void create_players(Player** players){
	for(int i = 0; i<NUMBER_OF_PLAYERS;i++){
		players[i]= malloc(sizeof(Player)); 
		current_game->players[0]->id = 0;
	}

}

void create_keyboardstate(){
		keyboardstate = malloc(sizeof(Keyboardstate));
		keyboardstate->turn_left = 0;
		keyboardstate->turn_right = 0;
		keyboardstate->go_forward = 0;
		keyboardstate->go_backwards = 0;
}
void delete_keyboardstate(){
	free(keyboardstate);
}


void start_new_game(){
	if(game_ongoing == 0){
		create_keyboardstate();
		current_game = malloc(sizeof(Game));
		current_game->angle = 0; 
		current_game->x = 100; 
		current_game->y = 100;
		
		game_ongoing = 1;
	}

}
Game* get_current_game(){
	return current_game;
}
Keyboardstate* get_keyboardstate(){
	return keyboardstate;
}
void end_game(){
	if(game_ongoing == 1){
		free(current_game);
		delete_keyboardstate();
		game_ongoing = 0;
	}
}
