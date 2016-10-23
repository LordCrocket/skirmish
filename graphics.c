#include "graphics.h"
#include "gamestate.h"
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>

sfRenderWindow* window;
sfTexture* texture;
sfSprite* sprite;
int fullscreen_on = 0;
int screen_w = 1920;
int screen_h = 1080;
int screen_props = sfResize | sfClose;


void init_screen(){
    sfVideoMode mode = {screen_w, screen_h, 32};
	if(sfVideoMode_isValid(mode)){
		if(window) destroy_graphics();
		window = sfRenderWindow_create(mode, "SFML window", screen_props, NULL);
	}
}


void toggle_fullscreen(){
	if(!fullscreen_on){
		screen_props = sfFullscreen | sfClose; 
		screen_w = 1920;
		screen_h = 1200;
		fullscreen_on = 1;
	}
	else{
		screen_props = sfResize | sfClose; 
		screen_w = 800;
		screen_h = 600;
		fullscreen_on = 0;
	}
	init_screen();

}

void create_sprite(char* filename){
	texture = sfTexture_createFromFile(filename, NULL);
    sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, sfTrue);
	sfVector2u size = sfTexture_getSize(texture);
	sfVector2f origin = {size.x/2,size.y/2};
    sfSprite_setOrigin(sprite, origin);
}
void resize(int width,int height){
	screen_w = width;
	screen_h = height;
	sfFloatRect view = {0,0,width,height};
	sfRenderWindow_setView(window,sfView_createFromRect(view));
}
int init_graphics() { 
	init_screen();
	create_sprite("image.bmp");
    if (!window) return EXIT_FAILURE;
    if (!sprite) return EXIT_FAILURE;
	return 0;
}
void destroy_graphics(){
	sfRenderWindow_close(window);
}

void draw_graphics(){
    sfRenderWindow_clear(window, sfWhite);
	Unit** all_units = malloc(get_number_of_players() * get_number_of_units() * sizeof(Unit*));
	get_all_units(all_units);
	for(int x; x < get_number_of_players() * get_number_of_units();x++){
		Unit* unit = all_units[x];	
		float x = unit->x;
		float y = unit->y;

		float angle = unit->angle;
		sfVector2f vector = {x,y};
		sfSprite_setPosition(sprite, vector);
		sfSprite_setRotation(sprite, angle);
    	sfRenderWindow_drawSprite(window, sprite, NULL);

	}
	free(all_units);
    sfRenderWindow_display(window);
}

int poll_event(sfEvent* event){
	return sfRenderWindow_pollEvent(window,event);
}

