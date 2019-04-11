#include "Audio.h"
#include <stdio.h>



Audio::Audio() {
	loadedMusic = NULL;
}

Audio::~Audio() {
	free();
}

bool Audio::initAudio() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s", Mix_GetError());
		return false;
	}
	return true;
}

bool Audio::loadAudio() {
	loadedMusic = Mix_LoadMUS("C:/Users/cupof/Music/againstTheCurent/01 Gravity.mp3");
	if (loadedMusic == NULL) {
		printf("Failed to load music! SDL_mixer Error: %s", Mix_GetError());
		return false;
	}
	return true;
}

void Audio::playMusic() {
	if (loadedMusic == NULL) {
		printf("Music has not been loaded yet");
		return;
	}

	if (Mix_PlayingMusic() == 0) {
		Mix_PlayMusic(loadedMusic, 0);
	}
}

void Audio::free() {
	if (loadedMusic != NULL) {
		Mix_FreeMusic(loadedMusic);
		loadedMusic = NULL;
	}
}