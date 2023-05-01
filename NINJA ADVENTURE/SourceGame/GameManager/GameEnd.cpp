#include "GameEnd.h"

GameEnd::GameEnd()
{
	again_btn = new Button();
	home_btn = new Button();
	nofi = new Text();
	score = new Text();
	highscore = new Text();
	bestscore = new Text();
	newrecord = new Text();
	texture_pos = { 0,0,0,0 };
	nofi->setColor(RED_COLOR);
	nofi_new = false;
	random[0] = CYAN_COLOR;
	random[1] = RED_COLOR;
	random[2] = YELLOW_COLOR;
	random[3] = PURPLE_COLOR;
}

GameEnd::~GameEnd()
{
}

void GameEnd::Init(SDL_Renderer* screen, TTF_Font* font)
{
	m_texture = IMG_LoadTexture(screen, m_mapTexture["Bkgrend"].c_str());
	SDL_QueryTexture(m_texture, NULL, NULL, &texture_pos.w, &texture_pos.h);
	again_btn->Init(screen, "Again", 5);
	again_btn->setPos(250, 400);
	home_btn->Init(screen, "Home", 6);
	home_btn->setPos(600, 400);
	nofi->setText("Play Again?");
	nofi->setPos(SCREEN_WIDTH / 4+125, SCREEN_HEIGHT / 3*2 - 50);
	nofi->LoadText(font, screen);
	nofi->setSize(280, 70);
}

void GameEnd::Update(SDL_Event* e, SDL_Renderer* screen, TTF_Font* font,const int& score_val)
{
	nofi_new = false;
	again_btn->Update(e);
	home_btn->Update(e);
	record = std::to_string(getHighScore("SourceGame//GameManager//record.txt"));
	bestscore->setText("Best: " + record);
	bestscore->LoadText(font, screen);
	bestscore->setPos(SCREEN_WIDTH / 2 - SCREEN_WIDTH / 4 - 30, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 8);
	cur_score = std::to_string(score_val);
	score->setText("Your score: " + cur_score);
	score->LoadText(font, screen);
	score->setPos(SCREEN_WIDTH *2 / 3, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 8);
	newrecord->setText("Congratulations.You've got a new record!!");
	newrecord->LoadText(font, screen);
	newrecord->setPos(SCREEN_WIDTH / 2 - SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 6);
	if (score_val >= getHighScore("SourceGame//GameManager//record.txt")) nofi_new = true;
	newrecord->setColor(random[rand() % 4]);
}

void GameEnd::RenderEnd(SDL_Renderer* screen)
{
	
	SDL_RenderCopy(screen, m_texture, NULL, &texture_pos);
	again_btn->RenderButton(screen);
	home_btn->RenderButton(screen);
	nofi->RenderText(screen);
	if (nofi_new) newrecord->RenderText(screen);
	else bestscore->RenderText(screen);
	score->RenderText(screen);
}
