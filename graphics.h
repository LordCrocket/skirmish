#include <SFML/Window/Event.h>
int init_graphics();
void destroy_graphics();
void draw_graphics();
void toggle_fullscreen();
void resize();
void zoom_out();
void zoom_in();
int poll_event(sfEvent*);
