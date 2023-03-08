#pragma once
#include "../GameManager/ResourceManager.h"

class Text
{
public:
	Text();
	~Text();
	void LoadText(TTF_Font* font, SDL_Renderer* screen);
	void Update();
	void setSize(int w,int h) { m_pos.w = w; m_pos.h = h; }
	void setPos(int x, int y) { m_pos.x = x; m_pos.y = y; }
	void setText(std::string newText) { m_text = newText; }
	void setColor(SDL_Color newColor) { m_color = newColor; }
	void RenderText(SDL_Renderer* screen);
	
private:
	std::string m_text;
	SDL_Color m_color;
	SDL_Rect m_pos;
	SDL_Texture* m_texture;
};