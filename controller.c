#include <stdio.h>
#include <SDL.h>
#include "gamestate.h"
#include <math.h>
#include "action.h"
#include "serverproxy.h"
#include "graphics.h"

int is_pressed(SDL_Event event){
	return (event.type == SDL_KEYDOWN);
}

void handle_keypress(SDL_Event event){

	SDLKey key = event.key.keysym.sym;
	if (event.type == SDL_KEYUP && key == fullscreen){
		toggle_fullscreen();
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

void send_actions_to_server(){
	if(get_keyboardstate()->go_forward)
		send_action(GO_FORWARD);
	if(get_keyboardstate()->go_backwards)
		send_action(GO_BACKWARDS);
	if(get_keyboardstate()->turn_left)
		send_action(TURN_LEFT);
	if(get_keyboardstate()->turn_right)
		send_action(TURN_RIGHT);
}

void update_state(){
	Unit** all_units = malloc(get_number_of_players() * get_number_of_players() * sizeof(Unit*));
	get_all_units(all_units); 
	update_unit_state(all_units);
	free(all_units);
}
