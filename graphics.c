#include <SDL.h>
#include "graphics.h"
#include "gamestate.h"
#include "SDL_opengl.h"

	GLuint block; 
	GLuint texture; 
	int fullscreen_on = 0;
	int screen_w = 800;
	int screen_h = 600;
	

void init_screen(){
	SDL_SetVideoMode(screen_w,screen_h,32, SDL_OPENGL | SDL_SWSURFACE);
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
}
void init_matrix(){
	glMatrixMode( GL_PROJECTION );
	glOrtho( 0, screen_w, screen_h, 0, -1, 1 );
    glMatrixMode( GL_MODELVIEW );
}
void create_sprite(GLuint* sprite,char* filename){
	glGenTextures( 1, sprite );
	SDL_Surface* image = SDL_LoadBMP(filename); 
    glBindTexture( GL_TEXTURE_2D, *sprite );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, 3, image->w, image->h, 0, 
                      GL_BGR, GL_UNSIGNED_BYTE, image->pixels );
					  
    if ( image ) { 
        SDL_FreeSurface( image );
    }

}

void init_opengl(){
	glClearColor( 255, 255, 255, 0 );
	glEnable( GL_TEXTURE_2D ); 
	init_matrix();	
	create_sprite(&texture,"image.bmp");
	create_sprite(&block,"block.bmp");

}
void toggle_fullscreen(){
	if(!fullscreen_on){
		
		screen_w = 1920;
		screen_h = 1200;
		fullscreen_on = 1;
		//glOrtho( 0, 1920, 1200, 0, -1, 1 );
	}
	else{
		screen_w = 800;
		screen_h = 600;
		fullscreen_on = 0;
		//glOrtho( 0, 800, 600, 0, -1, 1 );
	}
	init_screen();
	init_opengl();
		
}



int init_graphics() { 
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
		return -1;
	}
	init_screen();
	init_opengl();
	
    return 0;
}

void draw_graphics(){
	glClear( GL_COLOR_BUFFER_BIT );
	Unit** all_units = malloc(get_number_of_players() * get_number_of_units() * sizeof(Unit*));
	get_all_units(all_units);
	for(int x; x < get_number_of_players() * get_number_of_units();x++){
		Unit* unit = all_units[x];	
		float x = unit->x;
		float y = unit->y;
		float angle = unit->angle;

    	glBindTexture( GL_TEXTURE_2D, texture );
		if(angle != 0){

			glTranslatef(x+64,y+64,0);
			glRotatef(angle, 0.0, 0.0, 1.0);
			glTranslatef(-(x+64),-(y+64),0);
		}
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

	    glLoadIdentity();

	}
	free(all_units);

    SDL_GL_SwapBuffers();
    glLoadIdentity();
}



