#include "GameHighScore.h"

GameHighScore::GameHighScore()
{
	back_btn = new Button();
	texture_pos = { 0,0,0,0 };
}

GameHighScore::~GameHighScore()
{
}

void GameHighScore::Init(SDL_Renderer* screen, TTF_Font* font)
{
	m_texture = IMG_LoadTexture(screen, m_mapTexture["Bkgr_template"].c_str());
	SDL_QueryTexture(m_texture, NULL, NULL, &texture_pos.w, &texture_pos.h);
	back_btn->Init(screen, "Back", 7);
	back_btn->setPos(25, 25);
}

void GameHighScore::Update(SDL_Event* e)
{
	back_btn->Update(e);
}

void GameHighScore::RenderHighScore(SDL_Renderer* screen)
{
	SDL_RenderCopy(screen, m_texture, NULL, &texture_pos);
	back_btn->RenderButton(screen);
}