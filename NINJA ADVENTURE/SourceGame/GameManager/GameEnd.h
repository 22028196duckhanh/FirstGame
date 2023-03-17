#pragma once
#include "ResourceManager.h"

class GameEnd 
{
public:
	GameEnd();
	~GameEnd();	
	void Init(SDL_Renderer* screen, TTF_Font* font);
	void Update(SDL_Event* e);
	void RenderEnd(SDL_Renderer* screen);
	Button* again_btn;
	Button* home_btn;
private:
	SDL_Texture* m_texture;
	SDL_Rect texture_pos;
	Text* nofi;
	Text* score;
	Text* highscore;
};