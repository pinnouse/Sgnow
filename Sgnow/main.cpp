//Using SDL and standard IO
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <cmath>
#include <memory>

#include <string>
#include <vector>

#include "Colors.h"
#include "Audio.h"
#include "LTexture.h"
#include "FileReader.h"

std::unique_ptr<Audio> audio (new Audio);
LTexture* gTextTexture = NULL;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Global variables
SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

SDL_Surface* gHelloWorld = NULL;

TTF_Font* gFont = NULL;

bool init() {
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		//Create window
		gWindow = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			//Get window surface
			//gScreenSurface = SDL_GetWindowSurface(gWindow);
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			} else {
				int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1) {
					printf("SDL_ttf could not initiate! SDL Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}

	}
	if (!audio->initAudio()) {
		success = false;
	} else if (!audio->loadAudio()) {
		success = false;
	} else {
		audio->playMusic();
	}

	gTextTexture = new LTexture(gRenderer);

	std::vector<std::string> s = FileReader::readDir("C:/Users/cupof/Music");
	for (int i = 0; i < s.size(); i++) {
		printf("Folder: %s\n", s[i].c_str());
	}

	return success;
}

bool loadMedia() {
	//Loading success flag
	bool success = true;

	//Load splash image
	gHelloWorld = SDL_LoadBMP("02_getting_an_image_on_the_screen/hello_world.bmp");
	if (gHelloWorld == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", "hello_world.bmp", SDL_GetError());
		success = false;
	}

	gFont = TTF_OpenFont("Comfortaa-Regular.ttf", 28);
	if (gFont == NULL) {
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	} else {
		//Render text
		SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
		if (!gTextTexture->loadFromRenderedText("The quick brown fox jumps over the lazy dog", gFont, textColor)) {
			printf("Failed to render text texture!\n");
			success = false;
		}
	}

	return success;
}

void close() {
	audio->free();

	//Free loaded images
	gTextTexture->free();
	delete gTextTexture;
	gTextTexture = NULL;

	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;

	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}

int main(int argc, char* args[]) {

	if (!init()) {
		printf("Failed to initialize!\n");
	}
	else {
		//Load media
		if (!loadMedia()) {
			printf("Failed to load media!\n");
		}
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//While application is running
		while (!quit) {
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0) {
				//User requests quit
				if (e.type == SDL_QUIT) {
					quit = true;
				}
			}

			//Clear background
			SDL_SetRenderDrawColor(gRenderer, SgnowColors::DARK_NOT_BLACK[0], SgnowColors::DARK_NOT_BLACK[1], SgnowColors::DARK_NOT_BLACK[2], 0xFF);
			SDL_RenderClear(gRenderer);

			SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(gRenderer, &fillRect);

			//SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
			gTextTexture->setColor(SgnowColors::FULL_WHITE);
			gTextTexture->render(0, 0);

			//Update the surface
			//SDL_UpdateWindowSurface(gWindow);
			SDL_RenderPresent(gRenderer);
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}