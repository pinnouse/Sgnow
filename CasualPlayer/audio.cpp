#include "audio.h"

Audio::Audio() {}
void Audio::playSong(std::string path) {
	sf::Music music;
	if (!music.openFromFile(path)) {
		// File not found
	}

	music.play();
}