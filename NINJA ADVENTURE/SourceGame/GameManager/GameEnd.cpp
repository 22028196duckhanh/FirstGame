#include "GameEnd.h"

GameEnd::GameEnd()
{
	again_btn = new Button();
	home_btn = new Button();
	nofi = new Text();
	score = new Text();
	highscore = new Text();
	texture_pos = { 0,0,0,0 };
	nofi->setColor(RED_COLOR);
}

GameEnd::~GameEnd()
{
}

void GameEnd::Init(SDL_Renderer* screen, TTF_Font* font)
{
	m_texture = IMG_LoadTexture(screen, m_mapTexture["Bkgrend"].c_str());
	SDL_QueryTexture(m_texture, NULL, NULL, &texture_pos.w, &texture_pos.h);
	again_btn->Init(screen, "Again", 5);
	again_btn->setPos(250, 300);
	home_btn->Init(screen, "Home", 6);
	home_btn->setPos(600, 300);
	nofi->setText("Play Again?");
	nofi->setPos(SCREEN_WIDTH / 4+125, SCREEN_HEIGHT / 2-50);
	nofi->LoadText(font, screen);
	nofi->setSize(200, 50);
		
}

void GameEnd::Update( SDL_Event* e)
{
	again_btn->Update(e);
	home_btn->Update(e);
}

void GameEnd::RenderEnd(SDL_Renderer* screen)
{
	SDL_RenderCopy(screen, m_texture, NULL, &texture_pos);
	again_btn->RenderButton(screen);
	home_btn->RenderButton(screen);
	nofi->RenderText(screen);
}
