#include "GamePause.h"

GamePause::GamePause()
{
	resume_btn = new Button();
	home_btn = new Button();
}

GamePause::~GamePause()
{
}

void GamePause::Init(SDL_Renderer* screen, TTF_Font* font)
{
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
	resume_btn->RenderButton(screen);
	home_btn->RenderButton(screen);
}