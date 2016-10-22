#include "action.h"
#include "gamestate.h"
#include <math.h>
#include "serverproxy.h"
#include <stdio.h> 

int go_forward = 0;
int go_backwards = 0;
int turn_left = 0;
int turn_right = 0;

void send_action(Action action){
	switch(action){
		case GO_FORWARD: go_forward = 1;break;
		case GO_BACKWARDS: go_backwards = 1;break;
		case TURN_LEFT: turn_left = 1;break;
		case TURN_RIGHT: turn_right = 1;break;
	}
}

void update_unit_state(Unit** units){
	Unit* avatar = units[0];
	if(turn_right){
		avatar->angle+=3;
	}
	if(turn_left){
		avatar->angle-=3;
	}
	if(go_forward){
		avatar->x+= 3*sin(avatar->angle*M_PI/180);
		avatar->y-= 3*cos(avatar->angle*M_PI/180);
	}
	if(go_backwards){
		avatar->x-= sin(avatar->angle*M_PI/180);
		avatar->y+= cos(avatar->angle*M_PI/180);
	}
	go_forward = go_backwards = turn_left = turn_right = 0;
}
