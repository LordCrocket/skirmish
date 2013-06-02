#include <SDL.h>
#include <stdio.h>
#include "SDL_opengl.h"


int SDLEventFilter(const SDL_Event* filterEvent){
	if(filterEvent->type == SDL_MOUSEMOTION)
		return 0;
	
	return 1;
}

int toggle_fullscreen(SDL_Surface *screen){
	if (screen->flags & SDL_FULLSCREEN){
		screen = SDL_SetVideoMode(800,600,32,SDL_OPENGL | SDL_SWSURFACE);
	}
	else {
		screen = SDL_SetVideoMode(1900,1200,32,SDL_OPENGL|SDL_FULLSCREEN);
	}

}


int main(int argc, char** argv) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
		return -1;

	}
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); // *new*

	SDL_Surface* screen = SDL_SetVideoMode(800,600,32,SDL_OPENGL | SDL_SWSURFACE);//SDL_SWSURFACE | SDL_DOUBLEBUF);
	SDL_Event event;

    GLuint texture; // Texture object handle

	glClearColor( 255, 255, 255, 0 );
	glEnable( GL_TEXTURE_2D ); // Need this to display a texture

	 glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glOrtho( 0, 640, 480, 0, -1, 1 );
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

	Uint32 bgColor = SDL_MapRGB(screen->format, 255,0,0);
	Uint32 boxColor = SDL_MapRGB(screen->format, 0,0,0);
	SDL_FillRect(screen, NULL, bgColor);  
	SDL_Flip(screen);
	SDL_SetEventFilter(SDLEventFilter);
	int fps = 60;
	
    int tickInterval = 1000 / fps;
    Uint32 nextTick;	
	SDL_Surface* box = SDL_LoadBMP("image.bmp"); 
    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, 3, box->w, box->h, 0, 
                      GL_BGR, GL_UNSIGNED_BYTE, box->pixels );
					  
    if ( box ) { 
        SDL_FreeSurface( box );
    }
	

    glBindTexture( GL_TEXTURE_2D, texture );

	int x = 30;
	int y = 30;

	float degrees = 0;
		
	int quit = 0;
	int dpressed = 0;
	int apressed = 0;
	while(!quit){

	glClear( GL_COLOR_BUFFER_BIT );
		 nextTick = SDL_GetTicks() + tickInterval;
		    while (SDL_PollEvent(&event)){

				if (event.type == SDL_QUIT){
					quit = 1;
					break;
				}
				else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_f){
					toggle_fullscreen(screen);
				}else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_a){
					apressed = 1;
				}
				else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_a){
					apressed = 0;
				}
				else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d){
					dpressed = 1;
				}
				else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_d){
					dpressed = 0;
				}
			}
	if(dpressed){
					degrees++;

	}
	if(apressed){

					degrees--;
	}

	glTranslatef(164,164,0);
	glRotatef(degrees, 0.0, 0.0, 1.0);
	glTranslatef(-164,-164,0);

		glBegin( GL_QUADS );
        // Top-left vertex (corner)
        glTexCoord2i( 0, 0 );
        glVertex2f( 100, 100 );
    
        // Bottom-left vertex (corner)
        glTexCoord2i( 1, 0 );
        glVertex2f( 228, 100);
    
        // Bottom-right vertex (corner)
        glTexCoord2i( 1, 1 );
        glVertex2f( 228, 228);
    
        // Top-right vertex (corner)
        glTexCoord2i( 0, 1 );
        glVertex2f( 100, 228);
    glEnd();
    SDL_GL_SwapBuffers();
    glLoadIdentity();



		
		int delay = nextTick - SDL_GetTicks();
		if (delay > 0)
			SDL_Delay(delay);
	}
	SDL_Quit();
	return 0;
}
