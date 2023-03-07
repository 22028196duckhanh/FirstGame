#include "BulletSpawn.h"

BulletManager::BulletManager()
{
	m_BulletNum = 5;
}

BulletManager::~BulletManager()
{
}

void BulletManager::Init(Collision& collision, SDL_Renderer* screen)
{
	listBulletGround.resize(m_BulletNum);
	listBulletSky.resize(m_BulletNum);
	listPlayerSkill.resize(m_BulletNum);
	for (int i = 0; i < m_BulletNum; i++) {
		Bullet* bl = new Bullet();
		bl->Init(screen, "Bullet", "BulletImpact", 4, 3, 4, 3);
		bl->getHitBox()->isAlive = false;
		listBulletGround[i] = bl;
		collision.addObj(bl->getHitBox());
	}
	for (int i = 0; i < m_BulletNum; i++) {
		Bullet* bl = new Bullet();
		if (i==0) bl->Init(screen, "FireBall", "FireBallImpact", 4, 1, 4, 1);
		else if (i == 1) bl->Init(screen, "WaterBall", "WaterBallImpact", 7, 2, 4, 3);
		else if (i == 2) bl->Init(screen, "Thunder", "ThunderImpact", 10, 1, 5, 1);
		else if (i == 3) bl->Init(screen, "WaterTornado", "WaterTornadoImpact", 5, 1, 8, 1);
		else if (i == 4) bl->Init(screen, "Wind", "WindImpact", 6, 1, 4, 1);
		bl->getHitBox()->isAlive = false;
		bl->getHitBox()->tag = PLAYERSKILL;
		listPlayerSkill[i] = bl;
		collision.addObj(bl->getHitBox());
	}
	for (int i = 0; i < m_BulletNum; i++) {
		Bullet* bl = new Bullet();
		bl->Init(screen, "Boss2Skill", "Boss2SkillImpact", 7, 5, 15, 1);
		bl->getHitBox()->isAlive = false;
		listBulletSky[i] = bl;
		collision.addObj(bl->getHitBox());
	}
}

void BulletManager::Update(float deltaTime, Player* player, Boss1* boss1,Boss2* boss2)
{
	if (boss1->bulletAvailable==true) {
		SpawnGround();
		boss1->bulletAvailable = false;
	}
	if (player->useSkill == true) {
		SpawnPlayerSkill(player);
		player->skillAvailable = false;
		player->useSkill = false;
	}
	if (boss2->bulletAvailable == true && boss2->useSkill==false) {
		SpawnSky(player);
		boss2->useSkill = true;
		//boss2->bulletAvailable = false;
	}
	for (int i = 0; i < m_BulletNum ; i++) {
		listBulletGround[i]->Update(deltaTime);
		listPlayerSkill[i]->Update(deltaTime);
		listBulletSky[i]->Update(deltaTime);
	}
}

void BulletManager::renderBullet(SDL_Renderer* screen)
{
	for (int i = 0; i < m_BulletNum ; i++) {
		listBulletGround[i]->renderBullet(screen);
		listPlayerSkill[i]->renderBullet(screen);
		listBulletSky[i]->renderBullet(screen);
	}
}

void BulletManager::SpawnGround()
{
	Bullet* bl = NULL;
	for (int i = 0; i < m_BulletNum; i++) {
		if (listBulletGround[i]->getHitBox()->isAlive == false && listBulletGround[i]->isStop() == true) {
			bl = listBulletGround[i];
			break;
		}
	}
	if (bl == NULL) return;
	bl->getHitBox()->isAlive = true;
	//cr->setStop(false);
	bl->setPos(100.f, GROUND_Y - bl->getRect().h);
	bl->setVelo(180, 0);
	bl->reset();
}

void BulletManager::SpawnSky(Player*player)
{
	Bullet* bl = NULL;
	for (int i = 0; i < m_BulletNum; i++) {
		if (listBulletSky[i]->getHitBox()->isAlive == false && listBulletSky[i]->isStop() == true) {
			bl = listBulletSky[i];
			break;
		}
	}
	if (bl == NULL) return;
	bl->getHitBox()->isAlive = true;
	//cr->setStop(false);
	bl->setPos(player->getHitBox()->box.x, -300);
	bl->setVelo(rand()%31 -15, 200);
	bl->reset();
}

void BulletManager::SpawnPlayerSkill(Player* player)
{
	Bullet* bl = NULL;
	for (int i = rand()%4 +1; i < m_BulletNum; i++) {
		if (listPlayerSkill[i]->getHitBox()->isAlive == false && listPlayerSkill[i]->isStop() == true) {
			bl = listPlayerSkill[i];
			break;
		}
	}
	if (bl == NULL) return;
	bl->getHitBox()->isAlive = true;
	//cr->setStop(false);
	bl->setPos(player->getHitBox()->box.x+50, player->getHitBox()->box.y);
	if (bl == listPlayerSkill[3]) bl->setPos(player->getHitBox()->box.x + 50, player->getHitBox()->box.y - 40);
	bl->setVelo(200, 0);
	bl->reset();
}
