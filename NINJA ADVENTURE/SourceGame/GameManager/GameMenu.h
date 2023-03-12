#pragma once
#include "ResourceManager.h"
class GameMenu {
public:
	GameMenu();
	~GameMenu();
	void Init(SDL_Renderer* screen,TTF_Font* font);
	void Update(float deltaTime, SDL_Event* e);
	void RenderMenu(SDL_Renderer* screen);
	Button* play_btn;
	Button* info_btn;
	Button* setting_btn;
	Button* highscore_btn;
	Button* exit_btn;
private:
	SDL_Texture* menu_background;
	SDL_Rect bgr_pos;
	Animation* menu_player;
	SDL_Rect player_pos;
	Text* game_name;
};