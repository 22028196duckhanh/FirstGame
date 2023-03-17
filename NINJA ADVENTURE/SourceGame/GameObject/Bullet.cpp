#include "Bullet.h"

Bullet::Bullet()
{
	m_hitBox = new HitBox();
	m_rect = { 0,0,0,0 };
	m_hitBox->tag = BOSS_BULLET;
	m_hitBox->isAlive = true;
	m_hitBox->box = { 0,0,0,0 };
	m_stop = true;
}

Bullet::~Bullet()
{
	if (m_hitBox != NULL) {
		//delete m_hitBox;
		m_hitBox = NULL;
	}
	m_runAni->~Animation();
	m_deathAni->~Animation();
	m_curAni->~Animation();
	if (m_runAni != NULL) {
		//delete m_runAni;
		m_runAni = NULL;
	}
	if (m_deathAni != NULL) {
		//delete m_deathAni;
		m_deathAni = NULL;
	}
	if (m_curAni != NULL) {
		//delete m_curAni;
		m_curAni = NULL;
	}
}

void Bullet::Init(SDL_Renderer* screen, std::string name1, std::string name2, int x1, int y1, int x2, int y2)
{
	m_runAni = new Animation();
	m_runAni->Init(name1, x1, y1, screen);
	m_deathAni = new Animation();
	m_deathAni->Init(name2, x2, y2, screen);
	m_curAni = m_runAni;
	m_rect = { (int)pos.x,(int)pos.y,m_curAni->getRectSize().first,m_curAni->getRectSize().second };
}

void Bullet::Update(float deltaTime)
{
	if (m_stop) return;
	if (m_hitBox->isAlive) {
		m_curAni->Update();

		pos.x += velo.x * deltaTime;
		pos.y += velo.y * deltaTime;

		if (pos.x > SCREEN_WIDTH+100) { m_hitBox->isAlive = false; m_stop = true; }
		if (pos.y > GROUND_Y - m_rect.h+16 ) { m_hitBox->isAlive = false; pos.y -= 25; pos.x -= 20; }

		m_rect.x = (int)pos.x;
		m_rect.y = (int)pos.y;
		m_rect.w = m_curAni->getRectSize().first;
		m_rect.h = m_curAni->getRectSize().second;
		m_hitBox->box.x = (int)pos.x;
		m_hitBox->box.y = (int)pos.y;
		m_hitBox->box.w = m_curAni->getRectSize().first;
		m_hitBox->box.h = m_curAni->getRectSize().second;
	}
	else {
		m_curAni = m_deathAni;
		m_curAni->setEndFrame(true);
		m_curAni->slowFrame(2);
		m_curAni->Update();
		velo.x = 0;
		velo.y = 0;
		pos.x += velo.x * deltaTime;
		pos.y += velo.y * deltaTime;

		m_rect.x = (int)pos.x+20;
		m_rect.y = (int)pos.y-10;
		m_rect.w = m_curAni->getRectSize().first;
		m_rect.h = m_curAni->getRectSize().second;
		m_hitBox->box.x = (int)pos.x;
		m_hitBox->box.y = (int)pos.y;
		m_hitBox->box.w = m_curAni->getRectSize().first;
		m_hitBox->box.h =  m_curAni->getRectSize().second;
		if (m_curAni->checkEndFrame()) { m_stop = true; return; }
	}
}

void Bullet::renderBullet(SDL_Renderer*& screen)
{
	if (m_stop) return;
	m_curAni->renderAni(screen, m_rect);
	//SDL_RenderDrawRect(screen,&m_hitBox->box);
}

void Bullet::reset()
{
	m_stop = false;
	m_deathAni->reset();
	m_runAni->reset();
	m_curAni = m_runAni;
}
