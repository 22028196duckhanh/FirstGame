#pragma once
#include "../GameManager/ResourceManager.h"
#include "../GameManager/CollisionManager.h"
#include "Player.h"
#include "Boss1.h"
#include "Boss2.h"
#include "Bullet.h"


class BulletManager
{
public:
	BulletManager();
	~BulletManager();
	void Init(Collision& collision, SDL_Renderer* screen);
	void Update(float deltaTime,Player* player,Boss1 * boss1,Boss2 * boss2);
	void renderBullet(SDL_Renderer* screen);
	void SpawnGround();
	void SpawnSky(Player* player);
	void SpawnPlayerSkill(Player*player);
private:
	std::vector<Bullet*> listBulletGround;
	std::vector<Bullet*> listBulletSky;
	std::vector<Bullet*> listPlayerSkill;
	int m_BulletNum;
	
};