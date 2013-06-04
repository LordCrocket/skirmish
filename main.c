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

void toggle_fullscreen(SDL_Surface *screen){
	if (screen->flags & SDL_FULLSCREEN){
		screen = SDL_SetVideoMode(800,600,32,SDL_OPENGL | SDL_SWSURFACE);
	}
	else {
		screen = SDL_SetVideoMode(1900,1200,32,SDL_OPENGL|SDL_FULLSCREEN);
	}

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

