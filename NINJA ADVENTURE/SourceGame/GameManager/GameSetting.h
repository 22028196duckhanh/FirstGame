#pragma once
#include "ResourceManager.h"

class GameSetting
{
public:
	GameSetting();
	~GameSetting();
	void Init(SDL_Renderer* screen, TTF_Font* font);
	void Update(SDL_Event* e);
	void RenderSetting(SDL_Renderer* screen);
	Button* back_btn;
	Button* increase;
	Button* decrease;
	int power;
private:
	SDL_Texture* m_texture;
	SDL_Rect texture_pos;
	SDL_Texture* volume;
	std::vector<SDL_Rect> img;	
	SDL_Rect pos;
};