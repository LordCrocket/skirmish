#include <SDL.h>
#include <stdio.h>
#include <math.h>
#include "SDL_opengl.h"
#include "graphics.h"
#include "gamestate.h"
#include "controller.h"

int SDLEventFilter(const SDL_Event* filterEvent){
	if(filterEvent->type == SDL_MOUSEMOTION)
		return 0;
	
	return 1;
}



int main(int argc, char** argv) {

	init_graphics();
	start_new_game();

    SDL_SetEventFilter(SDLEventFilter);
    int fps = 60;
       
    int tickInterval = 1000 / fps;
       
    Uint32 nextTick; 

	int quit = 0;
	while(!quit){
		nextTick = SDL_GetTicks() + tickInterval;
		quit = handle_events();
		send_actions_to_server();
		update_state();
		draw_graphics();

		int delay = nextTick - SDL_GetTicks();
		if (delay > 0)
        	SDL_Delay(delay);
	}
       end_game();
       SDL_Quit();
       return 0;
}

