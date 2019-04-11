#include "LTexture.h"


LTexture::LTexture(SDL_Renderer* gRenderer) {
	mRenderer = gRenderer;
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}


LTexture::~LTexture() {
	free();
}

bool LTexture::loadFromFile(std::string path) {
	free();

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	} else {
		mTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
		if (mTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		} else {
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	return mTexture != NULL;
}

bool LTexture::loadFromRenderedText(std::string textureText, TTF_Font* gFont, SDL_Color textColor) {
	free();

	SDL_Surface* textSurface = TTF_RenderText_Blended(gFont, textureText.c_str(), textColor);
	
	if (textSurface == NULL) {
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	} else {
		mTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
		if (mTexture == NULL) {
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		} else {
			//Get width and height
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Free old texture
		SDL_FreeSurface(textSurface);
	}

	return mTexture != NULL; 
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(mRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setColor(Uint8 color[3]) {
	SDL_SetTextureColorMod(mTexture, color[0], color[1], color[2]);
}

void LTexture::setColor(const Uint8 color[3]) {
	SDL_SetTextureColorMod(mTexture, color[0], color[1], color[2]);
}

void LTexture::setBlendMode(SDL_BlendMode blending) {
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

int LTexture::getWidth() {
	return mWidth;
}

int LTexture::getHeight() {
	return mHeight;
}

void LTexture::free() {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}