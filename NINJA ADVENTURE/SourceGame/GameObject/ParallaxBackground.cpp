#include "ParallaxBackground.h"

void ParallaxBG::Init(SDL_Renderer*screen)
{
	Layer* layer;

	layer = new Layer();
	layer->Init("layer9", screen,1);
	BG.push_back(layer);

	layer = new Layer();
	layer->Init("layer8", screen,2);
	BG.push_back(layer);

	layer = new Layer();
	layer->Init("layer7", screen,3);
	BG.push_back(layer);

	layer = new Layer();
	layer->Init("layer6", screen,4);
	BG.push_back(layer);

	layer = new Layer();
	layer->Init("layer5", screen,5);
	BG.push_back(layer);

	layer = new Layer();
	layer->Init("layer4", screen,6);
	BG.push_back(layer);

	layer = new Layer();
	layer->Init("layer3", screen,7);
	BG.push_back(layer);

	layer = new Layer();
	layer->Init("layer2", screen,8);
	BG.push_back(layer);

	layer = new Layer();
	layer->Init("layer1", screen,9);
	BG.push_back(layer);
}

void ParallaxBG::Update()
{
	for (int i = 0; i < 9;i++) {
		BG[i]->Update();
	}
	SDL_Delay(10);
}

void ParallaxBG::RenderBG(SDL_Renderer* screen)
{
	for (int i = 0; i < 9; i++) {
		BG[i]->renderLayer(screen);
	}
}
