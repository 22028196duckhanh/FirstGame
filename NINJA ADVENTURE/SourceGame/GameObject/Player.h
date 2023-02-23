#pragma once
#include "../GameManager/ResourceManager.h"

enum STATUS {
	RUN=0,
	JUMP,
	FALL,
	ATTACK,
	DEATH
};

class Player
{
public:
	Player();
	~Player();
	void Init(SDL_Renderer* &screen);
	void InputAction();
	void ChangeStatus(int status);
	void Update(float deltaTime);
	void renderPlayer(SDL_Renderer* &screen);
	HitBox* getHitBox() { return m_hitBox; }
	bool skillAvailable;
private:
	int m_curStatus;
	int m_prevStatus;	
	bool useSkill;
	SDL_Rect m_rect;
	HitBox* m_hitBox;
	std::vector<Animation*> m_action;
	Vector2d pos;
	Vector2d velo;
	Vector2d move;
	
};