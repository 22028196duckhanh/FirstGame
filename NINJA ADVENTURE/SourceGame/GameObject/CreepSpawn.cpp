#include "CreepSpawn.h"

CreepManager::CreepManager()
{
	m_CreepNum = 5;
	m_TimeSpawnCreep = 2.f;
	m_currentTime = 0.f;
}

CreepManager::~CreepManager()
{

}

void CreepManager::Init(Collision& collision,SDL_Renderer* screen)
{
	listCreepGround.resize(m_CreepNum*3);
	listCreepSky.resize(m_CreepNum);
	for (int i = 0; i < m_CreepNum; i++) {
		Creep* cr = new Creep();
		cr->Init(screen, "GoblinRun", "GoblinDeath", 8, 1, 4, 1);
		cr->getHitBox()->isAlive = false;
		listCreepGround[i]=cr;
		collision.addObj(cr->getHitBox());
	}
	for (int i = m_CreepNum; i < m_CreepNum *2; i++) {
		Creep* cr = new Creep();
		cr->Init(screen, "SkeletonWalk", "SkeletonDeath", 4, 1, 4, 1);
		cr->getHitBox()->isAlive = false;
		listCreepGround[i] = cr;
		collision.addObj(cr->getHitBox());
	}
	for (int i = m_CreepNum *2; i < m_CreepNum *3; i++) {
		Creep* cr = new Creep();
		cr->Init(screen, "RinoRun", "RinoHit", 6, 1, 5, 1);
		cr->getHitBox()->isAlive = false;
		listCreepGround[i]=cr ;
		collision.addObj(cr->getHitBox());
	}

	for (int i = 0; i < m_CreepNum; i++) {
		Creep* cr = new Creep();
		cr->Init(screen, "BatFly", "BatHit", 7, 1, 5, 1);
		cr->getHitBox()->isAlive = false;
		listCreepSky[i] = cr;
		collision.addObj(cr->getHitBox());
	}
}

void CreepManager::Update(float deltaTime)
{
	m_currentTime += deltaTime;
	if (m_currentTime > m_TimeSpawnCreep) {
		SpawnGround();
		SpawnSky();
		m_currentTime = 0.f;
	}
	for (int i = 0; i < m_CreepNum *3;i++) {
		listCreepGround[i]->Update(deltaTime);
	}
	for (int i = 0; i < m_CreepNum; i++) {
		listCreepSky[i]->Update(deltaTime);
	}
}

void CreepManager::renderManyCreep(SDL_Renderer* screen)
{
	for (int i = 0; i < m_CreepNum * 3; i++) {
		listCreepGround[i]->renderCreep(screen);
	}
	for (int i = 0; i < m_CreepNum; i++) {
		listCreepSky[i]->renderCreep(screen);
	}
}
void CreepManager::SpawnGround()
{
	Creep* cr = NULL;
	for (int i = 0; i < m_CreepNum * 3; i+=(rand()%14+1)) {
		if (listCreepGround[i]->getHitBox()->isAlive==false && listCreepGround[i]->isStop()==true) {
			cr = listCreepGround[i];
			break;
		}
	}
	if (cr == NULL) return;
	cr->getHitBox()->isAlive=true;
	//cr->setStop(false);
	cr->setPos(SCREEN_WIDTH + rand() % (150 - 50 + 1) + 50, GROUND_Y - cr->getRect().h);
	cr->setVelo(-(200 + rand() % 50), 0);
	cr->reset();
}

void CreepManager::SpawnSky()
{
	Creep* cr = NULL;
	for (int i = 0; i < m_CreepNum; i++) {
		if (listCreepSky[i]->getHitBox()->isAlive == false && listCreepSky[i]->isStop() == true) {
			cr = listCreepSky[i];
			break;
		}
	}
	if (cr == NULL) return;
	cr->getHitBox()->isAlive = true;
	//cr->setStop(false);
	cr->setPos(SCREEN_WIDTH + rand() % (150 - 50 + 1) + 100, GROUND_Y - (rand() % (300 - 100 + 1) + 100));
	cr->setVelo(-(250 + rand() % 100), 0);
	cr->reset();
}
