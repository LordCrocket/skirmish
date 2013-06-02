#include <SDL.h>
#include <stdio.h>

int main(int argc, char** argv) {
SDL_Rect** modes;
	int i;
	modes = SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_HWSURFACE);
	if (modes == (SDL_Rect**)-1) {
		printf("All resolutions available.\n");
	}
	else {
printf("Available Modes\n");
for (i=0; modes[i]; ++i)
 printf("  %d x %d\n", modes[i]->w, modes[i]->h);

	}
}

