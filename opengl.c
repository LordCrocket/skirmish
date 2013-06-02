#include "SDL.h"
#include "SDL_opengl.h"

int main(int argc, char** argv){
	if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}
 
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); // *new*
 
	SDL_Surface* screen = SDL_SetVideoMode( 640, 480, 16, SDL_OPENGL | SDL_FULLSCREEN ); // *changed*
	glEnable( GL_TEXTURE_2D );
 
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
  
  	glViewport( 0, 0, 640, 480 );
	glClear( GL_COLOR_BUFFER_BIT );
    
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	 
	glOrtho(0.0f, 640, 480, 0.0f, -1.0f, 1.0f);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();






	return 0;

}
