#pragma once
#include "../GameManager/ResourceManager.h"
class Button
{
	enum BTN_TAG
	{
		PLAY,
		INFO,
		SETTING,
		HIGHSCORE,
		EXIT,
		AGAIN,
		HOME,
		BACK
	};
public:
	Button();
	~Button();
	void Init(SDL_Renderer* screen, std::string name,int tag);
	void Update(SDL_Event* e);
	void RenderButton(SDL_Renderer* screen);

	void HandleTouchEvent(SDL_Event* e);
	bool inside;
	bool isTouch;
	void setPos(int x, int y) { des.x = x; des.y = y; }

private:
	SDL_Rect des;
	SDL_Rect src[2];
	SDL_Texture* btn_image;
	int m_tag;
};