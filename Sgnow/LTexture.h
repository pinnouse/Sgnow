#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>

class LTexture {
public:
	LTexture(SDL_Renderer* gRenderer);
	~LTexture();

	bool loadFromFile(std::string path);

	bool loadFromRenderedText(std::string textureText, TTF_Font* gFont, SDL_Color textColor);

	void free();

	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setColor(Uint8 color[3]);
	void setColor(const Uint8 color[3]);

	void setBlendMode(SDL_BlendMode blending);

	void setAlpha(Uint8 alpha);

	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int getWidth();
	int getHeight();

private:
	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
};

