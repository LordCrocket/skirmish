#include <stdio.h>
#include <SDL.h>
#include "gamestate.h"
#include <math.h>
#include "action.h"
#include "serverproxy.h"

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
	Unit* avatar = get_avatar();

	if(get_keyboardstate()->turn_right){
		avatar->angle+=3;
	}
	if(get_keyboardstate()->turn_left){
		avatar->angle-=3;
	}
	if(get_keyboardstate()->go_forward){
		avatar->x+= 3*sin(avatar->angle*M_PI/180);
		avatar->y-= 3*cos(avatar->angle*M_PI/180);
	}
	if(get_keyboardstate()->go_backwards){
		avatar->x-= sin(avatar->angle*M_PI/180);
		avatar->y+= cos(avatar->angle*M_PI/180);
	}
}
