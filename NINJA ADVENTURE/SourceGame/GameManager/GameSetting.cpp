#include "GameSetting.h"

GameSetting::GameSetting()
{
	back_btn = new Button();
	texture_pos = { 0,0,0,0 };
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
}

void GameSetting::Update(SDL_Event* e)
{
	back_btn->Update(e);
}

void GameSetting::RenderSetting(SDL_Renderer* screen)
{
	SDL_RenderCopy(screen, m_texture, NULL, &texture_pos);
	back_btn->RenderButton(screen);
}
