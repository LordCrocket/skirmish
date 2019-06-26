#include <stdio.h>
#include <stdlib.h>
#include "gamestate.h"
#include <math.h>
#include "action.h"
#include "controller.h"
#include "serverproxy.h"
#include "graphics.h"
#include "sound.h"
#include <SFML/Window/Event.h>

int is_pressed(sfKeyCode key){
	return sfKeyboard_isKeyPressed(key);
}

void handle_keypress(sfEvent* event){

	sfKeyCode key = event->key.code;
	if (event->type == sfEvtKeyReleased){
		if(key == fullscreen){
			toggle_fullscreen();
		}
		else if (key == fire){
			play_sound(ORC_VOICE,0);
			play_sound(MACHINE_GUN,42);
		}
	}
	if(event->type == sfEvtKeyPressed){
		if (key == left){
			get_keyboardstate()->turn_left = is_pressed(key);
		}
		else if (key == right){
			get_keyboardstate()->turn_right = is_pressed(key);
		}
		else if (key == forward){
			get_keyboardstate()->go_forward = is_pressed(key);
		}
		else if (key == backwards){
			get_keyboardstate()->go_backwards = is_pressed(key);
		}
	}
}

void reset_unpressed_keys(){
		if(!is_pressed(left)) get_keyboardstate()->turn_left = 0;
		if(!is_pressed(right)) get_keyboardstate()->turn_right = 0;
		if(!is_pressed(forward)) get_keyboardstate()->go_forward = 0;
		if(!is_pressed(backwards)) get_keyboardstate()->go_backwards = 0;
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

			else if(event.type == sfEvtMouseWheelScrolled){
				if(event.mouseWheelScroll.delta < 0){
					zoom_out();
				}
				else {
					zoom_in();
				}
			}
	}

	reset_unpressed_keys();
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
