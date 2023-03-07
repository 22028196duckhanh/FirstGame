#pragma once
#include "../GameManager/ResourceManager.h"

class Bullet
{
public:
	Bullet();
	~Bullet();
	void Init(SDL_Renderer* screen, std::string name1, std::string name2, int x1, int y1, int x2, int y2);
	void Update(float deltaTime);
	void renderBullet(SDL_Renderer*& screen);
	void setPos(float x, float y) { pos.x = x; pos.y = y; }
	void setVelo(float x, float y) { velo.x = x; velo.y = y; }
	bool isStop() { return m_stop; }
	//void setStop(bool stop) { m_stop = stop; }
	HitBox* getHitBox() { return m_hitBox; }
	SDL_Rect getRect() { return m_rect; }
	void reset();
private:
	SDL_Rect m_rect;
	HitBox* m_hitBox;
	Animation* m_runAni;
	Animation* m_deathAni;
	Animation* m_curAni;
	Vector2d pos;
	Vector2d velo;
	bool m_stop;
};