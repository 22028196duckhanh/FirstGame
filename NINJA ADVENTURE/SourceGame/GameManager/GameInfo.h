#pragma once
#include "ResourceManager.h"

class GameInfo
{
public:
	GameInfo();
	~GameInfo();
	void Init(SDL_Renderer* screen, TTF_Font* font);
	void Update(SDL_Event* e);
	void RenderInfo(SDL_Renderer* screen);
	Button* back_btn;
private:
	SDL_Texture* m_texture;
	SDL_Rect texture_pos;
	SDL_Texture* character;
	SDL_Rect character_pos;
	
};