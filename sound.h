#include <SFML/Audio/Sound.h>
typedef enum  {
	ORC_VOICE,
	MACHINE_GUN
} SoundID;
typedef struct {
	SoundID id;
	int play;
	sfSoundBuffer* buffer;
	sfSound* sound;
} Sound;

void init_sound();
void play_sound(SoundID sound,int tick_delay);
void poll_sounds();
