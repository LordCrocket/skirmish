#include "gamestate.h"
#include <stdlib.h>

Game* current_game;
Keyboardstate* keyboardstate;


int game_ongoing = 0;

void start_new_game(){
	if(game_ongoing == 0){
		current_game = malloc(sizeof(Game));
		keyboardstate = malloc(sizeof(Keyboardstate));
		current_game->angle = 0; 
		current_game->x = 100; 
		current_game->y = 100;

		keyboardstate->turn_left = 0;
		keyboardstate->turn_right = 0;
		keyboardstate->go_forward = 0;
		keyboardstate->go_backwards = 0;

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
	free(current_game);
	free(keyboardstate);
	game_ongoing = 0;
}
