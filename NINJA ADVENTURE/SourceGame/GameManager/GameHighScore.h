#pragma once
#include "ResourceManager.h"

class GameHighScore
{
public:
	GameHighScore();
	~GameHighScore();
	void Init(SDL_Renderer* screen, TTF_Font* font);
	void Update(SDL_Event* e);
	void RenderHighScore(SDL_Renderer* screen);
	Button* back_btn;
private:
	SDL_Texture* m_texture;
	SDL_Rect texture_pos;


};