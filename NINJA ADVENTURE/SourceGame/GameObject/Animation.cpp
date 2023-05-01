#include "Animation.h"

Animation::Animation()
{
	m_rectSize = std::make_pair<int, int>(0, 0);
	m_frameNum= std::make_pair<int, int>(0, 0);
	src = { 0,0,0,0 };
	m_curFrame=0;
	m_width=0;
	m_height=0;
	m_Num=0;
	m_stopAtEndFrame = false;
	SLOW = 3;
}

Animation::~Animation()
{
	if (sprite != NULL) {
		SDL_DestroyTexture(sprite);
		sprite = NULL;
	}
	m_rectSize.first = 0;
	m_rectSize.second = 0;
	src = { 0,0,0,0 };
	m_curFrame = 0;
	m_width = 0;
	m_height = 0;
	m_Num = 0;
	m_stopAtEndFrame = false;
	SLOW = 0;
}

void Animation::CalculateSize(int width, int height) {
	m_rectSize.first = width / m_frameNum.first;
	m_rectSize.second = height / m_frameNum.second;
}


void Animation::setClips()
{
	for (int i = 0; i < m_Num; i++) {
		frame_clip[i].x = (i%m_frameNum.first) * m_rectSize.first;
		frame_clip[i].y = (i/m_frameNum.first)*m_rectSize.second;
		frame_clip[i].w = m_rectSize.first;
		frame_clip[i].h = m_rectSize.second;
	}
}
void Animation::Init(std::string name, int frameNumx, int frameNumy, SDL_Renderer* screen) {
	sprite = IMG_LoadTexture(screen, m_mapTexture[name].c_str());
	SDL_QueryTexture(sprite, NULL, NULL, &m_width, &m_height);
	m_frameNum.first = frameNumx;
	m_frameNum.second = frameNumy;
	m_Num = frameNumx * frameNumy;
	frame_clip.resize(m_Num);
	m_rectSize.first = 0;
	m_rectSize.second = 0;	
	CalculateSize(m_width, m_height);
	setClips();
}

void Animation::Update() {
	src = frame_clip[m_curFrame / SLOW];
	m_curFrame++;
	if (m_stopAtEndFrame == false) {
		if (m_curFrame >= m_Num * SLOW) m_curFrame -= m_Num * SLOW;
	}
	else {
		if (m_curFrame >= m_Num * SLOW) { m_curFrame = m_Num * SLOW - 1; }
	}
}


void Animation::renderAni(SDL_Renderer* &screen, SDL_Rect pos)
{
	SDL_RenderCopy(screen,sprite , &src , &pos);	
}

void Animation::reset()
{
	m_curFrame = 0;
	m_stopAtEndFrame = false;
}
