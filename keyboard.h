#include <SFML/Window/Event.h>
sfKeyCode forward;
sfKeyCode right;
sfKeyCode left;
sfKeyCode backwards;
sfKeyCode fullscreen;
typedef struct  {
	int turn_left;
	int turn_right;
	int go_forward;
	int go_backwards;
} Keyboardstate;

