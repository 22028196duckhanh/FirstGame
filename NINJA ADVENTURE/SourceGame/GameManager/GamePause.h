#pragma once
#include "ResourceManager.h"

class GamePause
{
public:
	GamePause();
	~GamePause();
	void Init(SDL_Renderer* screen, TTF_Font* font);
	void Update(SDL_Event* e);
	void RenderPause(SDL_Renderer* screen);
	Button* resume_btn;
	Button* home_btn;
private:
};