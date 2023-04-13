#include "GameSetting.h"

GameSetting::GameSetting()
{
	back_btn = new Button();
	img.resize(8);
	texture_pos = { 0,0,0,0 };
	power = 4;
	pos = { 200,200,0,0 };
}

GameSetting::~GameSetting()
{
}

void GameSetting::Init(SDL_Renderer* screen, TTF_Font* font)
{
	m_texture = IMG_LoadTexture(screen, m_mapTexture["Bkgr_template"].c_str());
	SDL_QueryTexture(m_texture, NULL, NULL, &texture_pos.w, &texture_pos.h);
	back_btn->Init(screen, "Back", 7);
	back_btn->setPos(25, 25);
	volume = IMG_LoadTexture(screen, m_mapTexture["Volume"].c_str());
	int x, y;
	SDL_QueryTexture(volume, NULL, NULL, &x, &y);
	for (int i = 0; i < 8; i++) {
		img[i].x = (i % 8) * x/8;
		img[i].y = (i / 8) * y;
		img[i].w = x/8;
		img[i].h = y;
	}
	pos.w = x / 8;
	pos.h = y;
}

void GameSetting::Update(SDL_Event* e)
{
	back_btn->Update(e);
	if (e->type == SDL_KEYDOWN) {
		if (e->key.keysym.sym == SDLK_b) {
			power--;
			if (power < 0) power = 0;
		}
		if (e->key.keysym.sym == SDLK_n) {
			power++;
			if (power > 7) power = 7;
		}
	}
}

void GameSetting::RenderSetting(SDL_Renderer* screen)
{
	SDL_RenderCopy(screen, m_texture, NULL, &texture_pos);
	back_btn->RenderButton(screen);
	SDL_RenderCopy(screen, volume, &img[power], &pos);
}
