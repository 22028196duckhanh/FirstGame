#pragma once
#include "ResourceManager.h"

class GameEnd 
{
public:
	GameEnd();
	~GameEnd();	
	void Init(SDL_Renderer* screen, TTF_Font* font);
	void Update(SDL_Event* e,SDL_Renderer* screen, TTF_Font* font,const int& score_val);
	void RenderEnd(SDL_Renderer* screen);
	Button* again_btn;
	Button* home_btn;
	bool nofi_new;
private:
	SDL_Texture* m_texture;
	SDL_Rect texture_pos;
	Text* nofi;	
	Text* highscore;
	std::string record;
	Text* bestscore;
	std::string cur_score;
	Text* score;
	Text* newrecord;
	SDL_Color random[4];
};