#include "gamestate.h"
#include <stdlib.h>

Game* current_game;
Keyboardstate* keyboardstate;


int game_ongoing = 0;
int PLAYER_ID = 0;
int NUMBER_OF_PLAYERS = 2;
int NUMBER_OF_UNITS = 2;


void create_units(Unit** units){
	for(int i = 0; i<NUMBER_OF_UNITS;i++){
		units[i]= malloc(sizeof(Unit)); 
		units[i]->angle = 0;
		units[i]->x = 0;
		units[i]->y = 0;
	}
}
void delete_units(Unit** units){

	for(int i = 0; i<NUMBER_OF_UNITS;i++){
		free(units[i]);
	}
}

void create_players(Player** players){

	for(int i = 0; i<NUMBER_OF_PLAYERS;i++){
		players[i]= malloc(sizeof(Player)); 
		players[i]->units = malloc(NUMBER_OF_UNITS * sizeof(Unit *));
		create_units(players[i]->units);
	}

}
void delete_players(Player** players){

	for(int i = 0; i<NUMBER_OF_PLAYERS;i++){
		delete_units(players[i]->units);
		free(players[i]->units);
		free(players[i]);
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
		current_game->players = malloc(NUMBER_OF_PLAYERS * sizeof(Player *));
		create_players(current_game->players);
		Unit* unit  = current_game->players[0]->units[0];
		unit->angle = 0;
		unit->x = 100;
		unit->y = 100;

		
		game_ongoing = 1;
	}
	else {
		fprintf(stderr,"Game already started!");	
	}

}
Game* get_current_game(){
	return current_game;
}
Keyboardstate* get_keyboardstate(){
	return keyboardstate;
}
Unit* get_avatar(){
	return current_game->players[0]->units[0];
}

void get_all_units(Unit** units){
	int number_of_units = 0;
	for(int x = 0; x< NUMBER_OF_PLAYERS; x++){
		for(int i = 0; i < NUMBER_OF_UNITS; i++){
			units[number_of_units++] = current_game->players[x]->units[i];
		}
	}
}

void end_game(){
	if(game_ongoing == 1){
		delete_players(current_game->players);
		delete_keyboardstate();
		free(current_game->players);
		free(current_game);
		game_ongoing = 0;
	}
	else{
		fprintf(stderr,"Game not started!");
	}
}
