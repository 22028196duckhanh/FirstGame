#include "GameEnd.h"

GameEnd::GameEnd()
{
	again_btn = new Button();
	home_btn = new Button();
	nofi = new Text();
	score = new Text();
	highscore = new Text();
	texture_pos = { 0,0,0,0 };
}

GameEnd::~GameEnd()
{
}

void GameEnd::Init(SDL_Renderer* screen, TTF_Font* font)
{
	m_texture = IMG_LoadTexture(screen, m_mapTexture["Bkground"].c_str());
	SDL_QueryTexture(m_texture, NULL, NULL, &texture_pos.w, &texture_pos.h);
	again_btn->Init(screen, "Again", 5);
	again_btn->setPos(0, 0);
	home_btn->Init(screen, "Home", 6);
	home_btn->setPos(400, 400);
	nofi->setText("Play Again?");
	nofi->setPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	nofi->LoadText(font, screen);

}

void GameEnd::Update(float deltaTime, SDL_Event* e)
{
	again_btn->Update(deltaTime, e);
	home_btn->Update(deltaTime, e);
}

void GameEnd::RenderEnd(SDL_Renderer* screen)
{
	again_btn->RenderButton(screen);
	home_btn->RenderButton(screen);
	nofi->RenderText(screen);
}
