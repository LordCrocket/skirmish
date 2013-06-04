#include <stdio.h>
#include <SDL.h>
#include "gamestate.h"
#include <math.h>

int is_pressed(SDL_Event event){
	return (event.type == SDL_KEYDOWN);
}

void handle_keypress(SDL_Event event){

	SDLKey key = event.key.keysym.sym;
	if (event.type == SDL_KEYUP && key == fullscreen){
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

int handle_events(){
	SDL_Event event;
	int quit = 0;
	while (SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT){
				quit = 1;
				break;
			}
			else if (event.type == SDL_KEYUP || SDL_KEYDOWN){
					handle_keypress(event);
			}
	}
	return quit;
}

void update_state(){
	Game* state = get_current_game();

	if(get_keyboardstate()->turn_right){
		state->angle+=3;
	}
	if(get_keyboardstate()->turn_left){
		state->angle-=3;
	}
	if(get_keyboardstate()->go_forward){
		state->x+= 3*sin(state->angle*M_PI/180);
		state->y-= 3*cos(state->angle*M_PI/180);
	}
	if(get_keyboardstate()->go_backwards){
		state->x-= sin(state->angle*M_PI/180);
		state->y+= cos(state->angle*M_PI/180);
	}
}
