#include "keyboard.h"
typedef struct  {
	int id;
} Player;

typedef struct {
	float angle;
	float x;
	float y;
} Unit;

typedef struct  {
	Player** players;
	float angle;
	float x;
	float y;
} Game;


void start_new_game();
void end_game();
Game* get_current_game();
Keyboardstate* get_keyboardstate();
int NUMBER_OF_PLAYERS;
int NUMBER_OF_UNITS;
