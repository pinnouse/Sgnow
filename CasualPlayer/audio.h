#pragma once

#include <string>
#include <SFML/Audio.hpp>

class Audio {
public:
	Audio();
	static void playSong(std::string path);
};