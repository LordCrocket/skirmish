#include <SDL.h>
SDLKey forward;
SDLKey right;
SDLKey left;
SDLKey back;
SDLKey fullscreen;

typedef struct  {
	int turn_left;
	int turn_right;
	int go_forward;
	int go_backwards;
} Keyboardstate;

