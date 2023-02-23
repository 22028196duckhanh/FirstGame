#pragma once
#include "../GameManager/ResourceManager.h"
#include "../GameManager/CollisionManager.h"
#include "Creep.h"


class CreepManager 
{
public:
	CreepManager();
	~CreepManager();
	void Init(Collision &collision, SDL_Renderer* screen);
	void Update(float deltaTime);
	void renderManyCreep(SDL_Renderer* screen);
private:
	std::vector<Creep*> listCreepGround;
	std::vector<Creep*> listCreepSky;
	int m_creepNum;
	void SpawnGround();
	void SpawnSky();
	int m_CreepNum;
	float m_TimeSpawnCreep;
	float m_currentTime;
};