#include "GameMenu.h"

GameMenu::GameMenu()
{
	menu_player = new Animation();
	play_btn = new Button();
	info_btn = new Button();
	setting_btn = new Button();
	highscore_btn = new Button();
	exit_btn = new Button();
	bgr_pos = { 0,0,0,0 };
	player_pos = { 0,0,0,0 };
	name_pos = { 0,0,0,0 };
}

GameMenu::~GameMenu()
{
}

void GameMenu::Init(SDL_Renderer* screen, TTF_Font* font)
{
	menu_background = IMG_LoadTexture(screen, m_mapTexture["Bkgrmenu"].c_str());	
	SDL_QueryTexture(menu_background, NULL, NULL, &bgr_pos.w, &bgr_pos.h);
	game_name = IMG_LoadTexture(screen, m_mapTexture["gametitle"].c_str());
	SDL_QueryTexture(game_name, NULL, NULL, &name_pos.w, &name_pos.h);
	name_pos.x = SCREEN_WIDTH / 2 - name_pos.w / 2;
	menu_player->Init("Idle", 8, 1, screen);
	player_pos = {  200,
					GROUND_Y- menu_player->getRectSize().second,
					menu_player->getRectSize().first  ,
					menu_player->getRectSize().second };
	play_btn->Init(screen, "Play", 0);
	play_btn->setPos(SCREEN_WIDTH / 2 - SCREEN_WIDTH / 9, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 6 - 80);
	info_btn->Init(screen, "Info", 1);
	info_btn->setPos(SCREEN_WIDTH / 3 - SCREEN_WIDTH / 9, SCREEN_HEIGHT - SCREEN_HEIGHT /4 - 80);
	setting_btn->Init(screen, "Setting", 2);
	setting_btn->setPos(SCREEN_WIDTH / 2 - SCREEN_WIDTH / 7, SCREEN_HEIGHT - SCREEN_HEIGHT / 4 - 80);
	highscore_btn->Init(screen, "HighScore", 3);
	highscore_btn->setPos(SCREEN_WIDTH / 3 *2 - SCREEN_WIDTH / 6, SCREEN_HEIGHT - SCREEN_HEIGHT / 4 - 80);
	exit_btn->Init(screen, "Exit", 4);
	exit_btn->setPos(SCREEN_WIDTH / 3*2, SCREEN_HEIGHT - SCREEN_HEIGHT / 4-80);
}

void GameMenu::Update(SDL_Event* e)
{
	menu_player->Update();
	play_btn->Update(e);
	info_btn->Update(e);
	setting_btn->Update(e);
	highscore_btn->Update(e);
	exit_btn->Update(e);
}

void GameMenu::RenderMenu(SDL_Renderer* screen)
{
	SDL_RenderCopy(screen, menu_background, NULL, &bgr_pos);
	SDL_RenderCopy(screen, game_name, NULL, &name_pos);
	play_btn->RenderButton(screen);
	info_btn->RenderButton(screen);
	setting_btn->RenderButton(screen);
	highscore_btn->RenderButton(screen);
	exit_btn->RenderButton(screen);
	menu_player->renderAni(screen, player_pos);
}
