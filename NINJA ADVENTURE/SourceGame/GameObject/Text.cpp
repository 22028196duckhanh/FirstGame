#include "Text.h"

Text::Text()
{
	m_text = "";
	m_color = WHITE_COLOR;
	m_pos = { 0,0,0,0 };
}

Text::~Text()
{
}

void Text::LoadText(TTF_Font* font,SDL_Renderer* screen)
{
	SDL_Surface* tmp = TTF_RenderText_Solid(font, m_text.c_str(), m_color);
	if (m_texture != NULL) { SDL_DestroyTexture(m_texture); }
	m_texture = SDL_CreateTextureFromSurface(screen, tmp);
	m_pos.w = tmp->w;
	m_pos.h = tmp->h;
	SDL_FreeSurface(tmp);
}

void Text::Update()
{
}

void Text::RenderText(SDL_Renderer* screen)
{
	SDL_RenderCopy(screen, m_texture, NULL, &m_pos);
}
