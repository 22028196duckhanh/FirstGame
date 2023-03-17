#include "Boss2.h"

Boss2::Boss2()
{
    m_skillTime = 4.f;
    m_curTime = 0.f;
    pos.x = -400.f;
    pos.y = float(GROUND_Y) - 250.f;
    velo.x = 200;
    velo.y = 0;
    bulletAvailable = false;
    pos_skill = { 0,0,96,736 };
    boss2spawn = false;
    useSkill = false;
}

Boss2::~Boss2()
{
    m_runStatus->~Animation();
    m_skillStatus->~Animation();
    if (m_runStatus != NULL) {
        delete m_runStatus; 
        m_runStatus = NULL;
    }
    if (m_skillStatus != NULL) {
        delete m_skillStatus;
        m_skillStatus = NULL;
    }
}

void Boss2::Init(SDL_Renderer*& screen)
{
    m_runStatus = new Animation();
    m_runStatus->Init("bossnhen1", 5, 4, screen);
    m_runStatus->slowFrame(2);
    m_skillStatus = new Animation();
    m_skillStatus->Init("bossnhen2", 10, 1, screen);
    m_rect = { (int)pos.x,(int)pos.y,m_runStatus->getRectSize().first,m_runStatus->getRectSize().second };
}

void Boss2::Update(float deltaTime)
{
    if (bulletAvailable == false) m_curTime += deltaTime;
    if (m_curTime > m_skillTime) {
        bulletAvailable = true;
        m_skillStatus->setEndFrame(true) ;
        m_curTime = 0.f;
    }
    m_runStatus->Update();
    if (bulletAvailable== true) {
        m_skillStatus->Update();
        if (m_skillStatus->checkEndFrame() == true) { m_skillStatus->reset(); bulletAvailable = false; useSkill = false; }
    }

    pos.x += velo.x * deltaTime;
    pos.y += velo.y * deltaTime;

    if (pos.x > (SCREEN_WIDTH - m_rect.w) / 2) pos.x = (SCREEN_WIDTH - m_rect.w) / 2;
    //if (pos.x < 0) pos.x = 0;

    m_rect.x = (int)pos.x;
    m_rect.y = (int)pos.y;
    m_rect.w = m_runStatus->getRectSize().first;
    m_rect.h = m_runStatus->getRectSize().second;
    
    pos_skill.x = m_rect.x + (m_rect.w - pos_skill.w) / 2 +8;
    pos_skill.y = m_rect.y - pos_skill.h+100;

}


void Boss2::renderBoss2(SDL_Renderer*& screen)
{
    if (bulletAvailable == true) m_skillStatus->renderAni(screen, pos_skill);
    m_runStatus->renderAni(screen, m_rect);
    
}
