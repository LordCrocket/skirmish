#include <SDL.h>
#include "gamestate.h"

int is_pressed(SDL_Event event){
	return (event.type == SDL_KEYDOWN);
}

void handle_keypress(SDL_Event event){

	SDLKey key = event.key.keysym.sym;
	if (event.type == SDL_KEYUP && key == SDLK_f){
	//				toggle_fullscreen(screen);
	}
	else if (key == left){
		get_keyboardstate()->turn_left = is_pressed(event);
	}
	else if (key == right){
		get_keyboardstate()->turn_right = is_pressed(event);
	}
	else if (key == forward){
		get_keyboardstate()->go_forward = is_pressed(event);
	}
	else if (key == back){
		get_keyboardstate()->go_backwards = is_pressed(event);
	}
						
}
