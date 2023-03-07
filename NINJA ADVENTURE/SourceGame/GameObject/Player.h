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
	HitBox* getProtectBox() { return protectBox; }
	bool skillAvailable;
	bool useSkill;
private:
	int m_curStatus;
	int m_prevStatus;	
	//float m_immortalTime;
	SDL_Rect m_rect;
	SDL_Rect skillslot;
	SDL_Rect liveslot;
	HitBox* m_hitBox;
	std::vector<Animation*> m_action;
	Animation* ImgSkillAvailable;
	Animation* ImgSkillCooldown;
	std::vector<SDL_Texture*> lives;
	Vector2d pos;
	Vector2d velo;
	Vector2d move;
	Animation* protect;
	SDL_Rect pos_protect;
	HitBox* protectBox;
	float protectTime;
};