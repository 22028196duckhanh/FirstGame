#include "GameInfo.h"

GameInfo::GameInfo()
{
	back_btn = new Button();
	character_pos = { 75,50,0,0 };
	texture_pos = { 0,0,0,0 };
}

GameInfo::~GameInfo()
{
}

void GameInfo::Init(SDL_Renderer* screen, TTF_Font* font)
{
	m_texture = IMG_LoadTexture(screen, m_mapTexture["Bkgr_template"].c_str());
	SDL_QueryTexture(m_texture, NULL, NULL, &texture_pos.w, &texture_pos.h);
	character = IMG_LoadTexture(screen, m_mapTexture["character"].c_str());
	SDL_QueryTexture(character, NULL, NULL, &character_pos.w, &character_pos.h);
	character_pos.w = character_pos.w * 2 / 3;
	character_pos.h = character_pos.h * 2 / 3;
	back_btn->Init(screen, "Back", 7);
	back_btn->setPos(25, 25);
}

void GameInfo::Update(SDL_Event* e)
{
	back_btn->Update(e);
}

void GameInfo::RenderInfo(SDL_Renderer* screen)
{
	SDL_RenderCopy(screen, m_texture, NULL, &texture_pos);
	SDL_RenderCopy(screen, character, NULL, &character_pos);
	back_btn->RenderButton(screen);
}
