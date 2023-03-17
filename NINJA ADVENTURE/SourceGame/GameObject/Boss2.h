#pragma once
#include "../GameManager/ResourceManager.h"

class Boss2
{
public:
	Boss2();
	~Boss2();
	void Init(SDL_Renderer*& screen);
	void Update(float deltaTime);
	void renderBoss2(SDL_Renderer*& screen);
	bool bulletAvailable;
	bool useSkill;
	bool boss2spawn;
	float m_skillTime;
private:
	SDL_Rect m_rect;
	SDL_Rect pos_skill;
	Animation* m_runStatus;
	Animation* m_skillStatus;
	Vector2d pos;
	Vector2d velo;
	
	float m_curTime;
};
