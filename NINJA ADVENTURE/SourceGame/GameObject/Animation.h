#pragma once
#include "../GameManager/ResourceManager.h"

class Animation
{
public:
	Animation();
	~Animation();
	void CalculateSize(int width, int height);
	void setClips();
	void Init(std::string name, int frameNumx, int frameNumy, SDL_Renderer* screen);
	void Update();
	void renderAni(SDL_Renderer* &screen, SDL_Rect pos);
	std::pair<int, int> getRectSize() { return m_rectSize; }
	void setEndFrame(bool stop) { m_stopAtEndFrame = stop; }
	void slowFrame(int slow) { SLOW = slow; }
	bool checkEndFrame() { return (m_curFrame == (m_Num*SLOW - 1)&&m_stopAtEndFrame==true); }
	void reset();
private:
	std::pair<int, int> m_rectSize;
	std::pair<int, int> m_frameNum;
	std::vector<SDL_Rect> frame_clip;
	SDL_Rect src;
	SDL_Texture* sprite;
	int m_curFrame;
	int m_width;
	int m_height;
	int m_Num;
	bool m_stopAtEndFrame;
	int SLOW;
};