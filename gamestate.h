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
} Game;


void start_new_game();
void end_game();
void get_all_units();
//Game* get_current_game();
Unit* get_avatar();
Keyboardstate* get_keyboardstate();
int NUMBER_OF_PLAYERS;
int NUMBER_OF_UNITS;
