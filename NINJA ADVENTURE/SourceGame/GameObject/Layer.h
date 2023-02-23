#pragma once
#include "../GameManager/ResourceManager.h"

class Layer
{
public:
	void Init(std::string name, SDL_Renderer* screen, int LAYERSPEED);
	void Update();	
	void renderLayer(SDL_Renderer* screen);
	int getSpeed() { return m_LAYERSPEED; }
private:
	SDL_Texture* layer;
	int m_LAYERSPEED;
	SDL_Rect m_rect1;
	SDL_Rect m_rect2;
};