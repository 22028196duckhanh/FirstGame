#pragma once
#include "Layer.h"
#include "../GameManager/ResourceManager.h"
#include "Boss2.h"

class ParallaxBG {
public:
	void Init(SDL_Renderer* screen);
	void Update();
	void RenderBG(SDL_Renderer* screen,Boss2* boss2);
private:
	std::vector<Layer*> BG;
};