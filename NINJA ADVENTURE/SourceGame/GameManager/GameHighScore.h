#pragma once
#include "ResourceManager.h"
#include <string>
class GameHighScore
{
public:
	GameHighScore();
	~GameHighScore();
	void Init(SDL_Renderer* screen, TTF_Font* font);
	void Update(SDL_Event* e, TTF_Font* font, SDL_Renderer* screen);
	void RenderHighScore(SDL_Renderer* screen);
	Button* back_btn;
	std::string score;
	Text* bestscore;
private:
	SDL_Texture* m_texture;
	SDL_Rect texture_pos;	

};