#include "keyboard.h"

typedef struct {
	float angle;
	float x;
	float y;
} Unit;

typedef struct  {
	Unit** units;
} Player;

typedef struct  {
	Player** players;
	int number_of_players;
	int number_of_units;
	int player_id;
} Game;


void start_new_game();
void end_game();
void get_all_units();
//Game* get_current_game();
int get_number_of_players();
int get_number_of_units();
Unit* get_avatar();
Keyboardstate* get_keyboardstate();
