#include "graphics.h"
#include "gamestate.h"
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>

sfRenderWindow* window;
sfView* windowView;

sfSprite* background;
sfTexture* background_texture;
sfTexture* texture;
sfSprite* sprite;

int fullscreen_on = 0;
int screen_w = 1920;
int screen_h = 1080;
int screen_props = sfResize | sfClose;
float zoom = 1;
//int screen_props = sfFullscreen | sfClose;


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

void add_background(){
	sfIntRect size = { 0,0,4096,4096 };
	background_texture = sfTexture_createFromFile("background.png", NULL);
	sfTexture_setSmooth(background_texture,sfFalse);
	sfTexture_setRepeated(background_texture,sfTrue);

    background = sfSprite_create();
    sfSprite_setTexture(background, background_texture, sfTrue);
	sfSprite_setTextureRect(background,size);
	sfVector2f position = { -2048,-2048};
	sfSprite_setPosition(background,position);
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
	add_background();
	create_sprite("octo.png");
    if (!window) return EXIT_FAILURE;
    if (!sprite) return EXIT_FAILURE;
	return 0;
}
void destroy_graphics(){
	sfRenderWindow_close(window);
}

void center_on_player(Unit* player){
	float x = player->x;
	float y = player->y;
	float angle = player->angle;
	sfFloatRect view = {0,0,screen_w,screen_h};
	sfVector2f vector = {x,y};
	sfView * sfView = sfView_createFromRect(view);
	sfView_setCenter(sfView,vector);
	sfView_rotate (sfView,angle);
	windowView = sfView;
}

void zoom_view (float factor){
	sfView_zoom(windowView,factor);
}
void zoom_out(){
	zoom += 0.1;
}
void zoom_in(){
	if(zoom > 0.1){
		zoom -= 0.1;
	}
}


void draw_graphics(){
    sfRenderWindow_clear(window, sfWhite);
	sfRenderWindow_drawSprite(window, background, NULL);
	Unit** all_units = malloc(get_number_of_players() * get_number_of_units() * sizeof(Unit*));
	get_all_units(all_units);
	for(int x = 0; x < get_number_of_players() * get_number_of_units();x++){
		Unit* unit = all_units[x];
		float x = unit->x;
		float y = unit->y;

		float angle = unit->angle;
		sfVector2f vector = {x,y};
		sfSprite_setPosition(sprite, vector);
		sfSprite_setRotation(sprite, angle);
    	sfRenderWindow_drawSprite(window, sprite, NULL);

	}
	Unit* player = all_units[0];	
	center_on_player(player);
	zoom_view(zoom);

	sfRenderWindow_setView(window,windowView);

	free(all_units);
    sfRenderWindow_display(window);
}

int poll_event(sfEvent* event){
	return sfRenderWindow_pollEvent(window,event);
}

