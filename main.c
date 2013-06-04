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
	SDL_Event event;
	
    Uint32 nextTick;	

    GLuint texture; 
    glGenTextures( 1, &texture );
	SDL_Surface* box = SDL_LoadBMP("image.bmp"); 
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, 3, box->w, box->h, 0, 
                      GL_BGR, GL_UNSIGNED_BYTE, box->pixels );
					  
    if ( box ) { 
        SDL_FreeSurface( box );
    }
	

    glBindTexture( GL_TEXTURE_2D, texture );

	float x;
	float y;

	float degrees = 0;
		
	int quit = 0;
	while(!quit){
		x = get_current_game()->x;
		y = get_current_game()->y;

		glClear( GL_COLOR_BUFFER_BIT );
		nextTick = SDL_GetTicks() + tickInterval;
		    while (SDL_PollEvent(&event)){

				if (event.type == SDL_QUIT){
					quit = 1;
					break;
				}
				else if (event.type == SDL_KEYUP || SDL_KEYDOWN){
					handle_keypress(event);
				}
			}
	if(get_keyboardstate()->turn_right){
					degrees+=3;
	}
	if(get_keyboardstate()->turn_left){
					degrees-=3;
	}
	if(get_keyboardstate()->go_forward){
		y = y-3*cos(degrees*M_PI/180);
		x = x+3*sin(degrees*M_PI/180);
	}
	if(get_keyboardstate()->go_backwards){
		y = y+cos(degrees*M_PI/180);
		x = x-sin(degrees*M_PI/180);
	}
	get_current_game()->x = x;
	get_current_game()->y = y;

	glTranslatef(x+64,y+64,0);
	glRotatef(degrees, 0.0, 0.0, 1.0);
	glTranslatef(-(x+64),-(y+64),0);

		glBegin( GL_QUADS );
        // Top-left vertex (corner)
        glTexCoord2i( 0, 0 );
        glVertex2f( x, y );
    
        // Bottom-left vertex (corner)
        glTexCoord2i( 1, 0 );
        glVertex2f( 128+x, y);
    
        // Bottom-right vertex (corner)
        glTexCoord2i( 1, 1 );
        glVertex2f( 128+x, 128+y);
    
        // Top-right vertex (corner)
        glTexCoord2i( 0, 1 );
        glVertex2f( x, 128+y);
    glEnd();


    SDL_GL_SwapBuffers();
    glLoadIdentity();



		
		int delay = nextTick - SDL_GetTicks();
		if (delay > 0)
			SDL_Delay(delay);
	}
	end_game();
	SDL_Quit();
	return 0;
}
