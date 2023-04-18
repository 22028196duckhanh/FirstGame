#include "GamePause.h"

GamePause::GamePause()
{
	resume_btn = new Button();
	home_btn = new Button();
	//texture_pos = { 0,0,0,0 };
}

GamePause::~GamePause()
{
}

void GamePause::Init(SDL_Renderer* screen, TTF_Font* font)
{
	//m_texture = IMG_LoadTexture(screen, m_mapTexture["Bkgr_template"].c_str());
	//SDL_QueryTexture(m_texture, NULL, NULL, &texture_pos.w, &texture_pos.h);
	resume_btn->Init(screen, "Resume", 0);
	resume_btn->setPos(SCREEN_WIDTH-76, 0);
	home_btn->Init(screen, "Home", 6);
	home_btn->setPos(SCREEN_WIDTH/2-40, 100);
}

void GamePause::Update(SDL_Event* e)
{
	resume_btn->Update(e);
	home_btn->Update(e);
}

void GamePause::RenderPause(SDL_Renderer* screen)
{
	//SDL_RenderCopy(screen, m_texture, NULL, &texture_pos);
	resume_btn->RenderButton(screen);
	home_btn->RenderButton(screen);
}