#include "sound.h"
#include <SFML/Audio/Sound.h>
#include <SFML/Audio/SoundBuffer.h>

Sound orc_voice = { ORC_VOICE, -1 };
Sound machine_gun = { MACHINE_GUN, -1 };

void init_sound(){
	orc_voice.buffer = sfSoundBuffer_createFromFile("sounds/orc_voice.ogg");
	orc_voice.sound = sfSound_create();
	sfSound_setBuffer(orc_voice.sound,orc_voice.buffer);

	machine_gun.buffer = sfSoundBuffer_createFromFile("sounds/machine_gun.ogg");
	machine_gun.sound = sfSound_create();
	sfSound_setBuffer(machine_gun.sound,machine_gun.buffer);
}
void play_sound(SoundID sound, int tick_delay){
	switch(sound){
		case ORC_VOICE: if(orc_voice.play < 0) orc_voice.play = tick_delay; break;
		case MACHINE_GUN: if(machine_gun.play < 0) machine_gun.play = tick_delay; break;
	}
}

void poll_sounds(){
	if(orc_voice.play == 0){
		sfSound_play(orc_voice.sound);
	}
	if(machine_gun.play == 0){
		sfSound_play(machine_gun.sound);
	}
	if(orc_voice.play > -1) orc_voice.play--;
	if(machine_gun.play > -1) machine_gun.play--;
}
