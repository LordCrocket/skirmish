#include "keyboard.h"
typedef struct  {
	int angle;
	float x;
	float y;
} Game;


void start_new_game();
void end_game();
Game* get_current_game();
Keyboardstate* get_keyboardstate();
