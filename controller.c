#include <stdio.h>
#include <stdlib.h>
#include "gamestate.h"
#include <math.h>
#include "action.h"
#include "serverproxy.h"
#include "graphics.h"
#include <SFML/Window/Event.h>

int is_pressed(sfEvent* event){
	return (event->type == sfEvtKeyPressed);
}

void handle_keypress(sfEvent* event){

	sfKeyCode key = event->key.code;
	if (event->type == sfEvtKeyPressed && key == fullscreen){
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
	sfEvent event;
	int quit = 0;
	while (poll_event(&event)){
			if (event.type == sfEvtClosed){
				quit = 1;
				break;
			}
			else if ((event.type == sfEvtKeyPressed) || (event.type == sfEvtKeyReleased)){
				handle_keypress(&event);
			}
			else if (event.type == sfEvtResized){
				resize(event.size.width,event.size.height);
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
