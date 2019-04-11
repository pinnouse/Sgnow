#pragma once
#include <SDL_mixer.h>

class Audio {
private:
	Mix_Music *loadedMusic;

public:
	Audio();
	~Audio();

	bool initAudio();
	bool loadAudio();
	void playMusic();

	void free();
};

