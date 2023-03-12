#include "GameMenu.h"

GameMenu::GameMenu()
{
	menu_player = new Animation();
	game_name = new Text();
	play_btn = new Button();
	info_btn = new Button();
	setting_btn = new Button();
	highscore_btn = new Button();
	exit_btn = new Button();
	bgr_pos = { 0,0,0,0 };
	player_pos = { 0,0,0,0 };
}

GameMenu::~GameMenu()
{
}

void GameMenu::Init(SDL_Renderer* screen, TTF_Font* font)
{
	menu_background = IMG_LoadTexture(screen, m_mapTexture["Bkground"].c_str());	
	game_name->setText("NINJA ADVENTURE");
	game_name->LoadText(font, screen);	
	game_name->setPos(SCREEN_WIDTH / 2 - 125,0);
	game_name->setSize(250, 50);
	SDL_QueryTexture(menu_background, NULL, NULL, &bgr_pos.w, &bgr_pos.h);
	menu_player->Init("Idle", 8, 1, screen);
	player_pos = { SCREEN_WIDTH / 2 - SCREEN_WIDTH / 16,
					SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 7 - menu_player->getRectSize().second * 2,
					menu_player->getRectSize().first * 2 ,
					menu_player->getRectSize().second * 2 };
	play_btn->Init(screen, "Play", 0);
	play_btn->setPos(SCREEN_WIDTH / 2 - SCREEN_WIDTH / 9, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 6);
	info_btn->Init(screen, "Info", 1);
	info_btn->setPos(SCREEN_WIDTH / 3 - SCREEN_WIDTH / 9, SCREEN_HEIGHT - SCREEN_HEIGHT /4);
	setting_btn->Init(screen, "Setting", 2);
	setting_btn->setPos(SCREEN_WIDTH / 2 - SCREEN_WIDTH / 7, SCREEN_HEIGHT - SCREEN_HEIGHT / 4);
	highscore_btn->Init(screen, "HighScore", 3);
	highscore_btn->setPos(SCREEN_WIDTH / 3 *2 - SCREEN_WIDTH / 6, SCREEN_HEIGHT - SCREEN_HEIGHT / 4);
	exit_btn->Init(screen, "Exit", 4);
	exit_btn->setPos(SCREEN_WIDTH / 3*2, SCREEN_HEIGHT - SCREEN_HEIGHT / 4);
}

void GameMenu::Update(float deltaTime,SDL_Event* e)
{
	menu_player->Update();
	play_btn->Update(deltaTime, e);
	info_btn->Update(deltaTime, e);
	setting_btn->Update(deltaTime, e);
	highscore_btn->Update(deltaTime, e);
	exit_btn->Update(deltaTime, e);
}

void GameMenu::RenderMenu(SDL_Renderer* screen)
{
	SDL_RenderCopy(screen, menu_background, NULL, &bgr_pos);
	play_btn->RenderButton(screen);
	info_btn->RenderButton(screen);
	setting_btn->RenderButton(screen);
	highscore_btn->RenderButton(screen);
	exit_btn->RenderButton(screen);
	menu_player->renderAni(screen, player_pos);
	game_name->RenderText(screen);
}
