#pragma once
#include "Layer.h"
#include "../GameManager/ResourceManager.h"

class ParallaxBG {
public:
	void Init(SDL_Renderer* screen);
	void Update();
	void RenderBG(SDL_Renderer* screen);
private:
	std::vector<Layer*> BG;
};