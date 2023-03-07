#pragma once
#include "../GameManager/ResourceManager.h"

enum BOSSSTATUS {
	BOSSJUMP,
	BOSSBITE,
	BOSSSKILL
};

class Boss1
{
public:
	Boss1();
	~Boss1();
	void Init(SDL_Renderer*& screen);
	void ChangeStatus(int status);
	void Update(float deltaTime);
	void renderBoss1(SDL_Renderer*& screen);
	HitBox* getHitBox() { return m_hitBox; }
	bool bulletAvailable;
private:
	int m_curStatus;
	int m_prevStatus;
	SDL_Rect m_rect;
	HitBox* m_hitBox;
	std::vector<Animation*> m_action;
	Vector2d pos;
	Vector2d velo;
	float m_changeTime;
	float m_curTime;

};