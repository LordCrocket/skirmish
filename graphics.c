#include <SDL.h>
#include "graphics.h"
#include "SDL_opengl.h"
void init_screen(){

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	SDL_SetVideoMode(800,600,32,SDL_OPENGL | SDL_SWSURFACE);
	glClearColor( 255, 255, 255, 0 );

}

void init_matrix(){

	glMatrixMode( GL_PROJECTION );
	glOrtho( 0, 640, 480, 0, -1, 1 );
    glMatrixMode( GL_MODELVIEW );
}

int init_graphics() { 
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
		return -1;
	}
	init_screen();
	glEnable( GL_TEXTURE_2D ); // Need this to display a texture
	init_matrix();	
	
    return 0;
}



