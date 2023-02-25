#include "CreepSpawn.h"

CreepManager::CreepManager()
{
	m_TimeSpawnCreep = 2.5f;
	m_currentTime = 0.f;
	m_creepNum = 3;
	
}

CreepManager::~CreepManager()
{

}

void CreepManager::Init(Collision& collision,SDL_Renderer* screen)
{
	
	listCreepGround.resize(m_creepNum*3);
	listCreepSky.resize(m_creepNum*3);
	for (int i = 0; i < m_creepNum*3; i+=m_creepNum) {
		Creep* cr = new Creep();
		cr->Init(screen, "GoblinRun", "GoblinDeath", 8, 1, 4, 1);
		cr->getHitBox()->isAlive = false;
		listCreepGround[i]=cr;
		collision.addObj(cr->getHitBox());
	}
	for (int i =1; i < m_creepNum *3; i+=m_creepNum) {
		Creep* cr = new Creep();
		cr->Init(screen, "SkeletonWalk", "SkeletonDeath", 4, 1, 4, 1);
		cr->getHitBox()->isAlive = false;
		listCreepGround[i] = cr;
		collision.addObj(cr->getHitBox());
	}
	for (int i = 2; i < m_creepNum *3; i+=m_creepNum) {
		Creep* cr = new Creep();
		cr->Init(screen, "RinoRun", "RinoHit", 6, 1, 5, 1);
		cr->getHitBox()->isAlive = false;
		listCreepGround[i]=cr ;
		collision.addObj(cr->getHitBox());
	}

	for (int i = 0; i < m_creepNum * 3; i += m_creepNum) {
		Creep* cr = new Creep();
		cr->Init(screen, "BatFly", "BatHit", 7, 1, 5, 1);
		cr->getHitBox()->isAlive = false;
		listCreepSky[i] = cr;
		collision.addObj(cr->getHitBox());
	}
	for (int i = 1; i < m_creepNum * 3; i += m_creepNum) {
		Creep* cr = new Creep();
		cr->Init(screen, "EyesFly", "EyesHit", 8, 1, 4, 1);
		cr->getHitBox()->isAlive = false;
		listCreepSky[i] = cr;
		collision.addObj(cr->getHitBox());
	}
	for (int i = 2; i < m_creepNum * 3; i += m_creepNum) {
		Creep* cr = new Creep();
		cr->Init(screen, "PurpleFly", "PurpleHit", 6, 1, 3, 1);
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
	for (int i = 0; i < m_creepNum*3;i++) {
		listCreepGround[i]->Update(deltaTime);
	}
	for (int i = 0; i < m_creepNum*3; i++) {
		listCreepSky[i]->Update(deltaTime);
	}
}

void CreepManager::renderManyCreep(SDL_Renderer* screen)
{
	for (int i = 0; i < m_creepNum * 3; i++) {
		listCreepGround[i]->renderCreep(screen);
	}
	for (int i = 0; i < m_creepNum*3; i++) {
		listCreepSky[i]->renderCreep(screen);
	}
}
void CreepManager::SpawnGround()
{
	Creep* cr = NULL;
	for (int i = rand()%9; i < m_creepNum * 3; i++) {
		if (listCreepGround[i]->getHitBox()->isAlive==false && listCreepGround[i]->isStop()==true) {
			cr = listCreepGround[i];
			break;
		}
	}
	if (cr == NULL) return;
	cr->getHitBox()->isAlive=true;
	//cr->setStop(false);
	cr->setPos(SCREEN_WIDTH + rand() % (150 - 50 + 1) + 50, GROUND_Y - cr->getRect().h);
	cr->setVelo(-(200 + rand() % 75), 0);
	cr->reset();
}

void CreepManager::SpawnSky()
{
	Creep* cr = NULL;
	for (int i = rand()%9; i < m_creepNum*3; i++) {
		if (listCreepSky[i]->getHitBox()->isAlive == false && listCreepSky[i]->isStop() == true) {
			cr = listCreepSky[i];
			break;
		}
	}
	if (cr == NULL) return;
	cr->getHitBox()->isAlive = true;
	//cr->setStop(false);
	cr->setPos(SCREEN_WIDTH + rand() % (150 - 50 + 1) + 100, GROUND_Y - (rand() % (250 - 100 + 1) + 100));
	cr->setVelo(-(400 + rand() % 100), 0);
	cr->reset();
}
