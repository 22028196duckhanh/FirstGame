#include "Layer.h"

Layer::Layer()
{
}

Layer::~Layer()
{
	if (layer != NULL) {
		SDL_DestroyTexture(layer);
		layer = NULL;
	}
}

void Layer::Init(std::string name, SDL_Renderer* screen, int LAYERSPEED)
{
	layer = IMG_LoadTexture(screen, m_mapTexture[name].c_str());
	SDL_QueryTexture(layer, NULL, NULL, &m_rect1.w, &m_rect1.h);
	m_rect2 = { m_rect1.w,0,m_rect1.w,m_rect1.h };
	m_LAYERSPEED = LAYERSPEED;
}

void Layer::Update()
{
	m_rect1.x -= m_LAYERSPEED;
	m_rect2.x -= m_LAYERSPEED;
	if (m_rect1.x <= -m_rect1.w) { m_rect1.x = m_rect1.w; }
	if (m_rect2.x <= -m_rect1.w) { m_rect2.x = m_rect2.w; }

}

void Layer::renderLayer(SDL_Renderer* screen)
{
	SDL_RenderCopy(screen, layer, NULL, &m_rect1);
	SDL_RenderCopy(screen, layer, NULL, &m_rect2);
}
