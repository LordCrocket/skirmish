#include <SFML/System/Time.h>
#include <SFML/System/Export.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "gamestate.h"
#include "controller.h"

//int SDLEventFilter(const SDL_Event* filterEvent){
//	if(filterEvent->type == SDL_MOUSEMOTION)
//		return 0;
//
//	return 1;
//}


int get_ticks(sfClock* clock){
	return sfTime_asMilliseconds(sfClock_getElapsedTime(clock));
}

int main(int argc, char** argv) {
	sfClock* clock = sfClock_create();

	init_graphics();
	start_new_game();

	int fps = 60;

	int tickInterval = 1000 / fps;

	int nextTick; 

	int quit = 0;
	while(!quit){
		nextTick = get_ticks(clock) + tickInterval;
		quit = handle_events();
		//update_keyboardstate();
		send_actions_to_server();
		update_state();
		draw_graphics();

		int delay = nextTick - get_ticks(clock);
		if (delay > 0){
			sfSleep(sfMilliseconds(delay));
		}
	}
	end_game();
	sfClock_destroy(clock);
	destroy_graphics();
    return EXIT_SUCCESS;
}

