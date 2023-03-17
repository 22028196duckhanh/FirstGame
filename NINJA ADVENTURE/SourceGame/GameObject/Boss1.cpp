#include "Boss1.h"

Boss1::Boss1()
{
    m_hitBox = new HitBox();
    m_hitBox->box = { 0,0,230,180 };
    m_hitBox->isAlive = true;
    m_curStatus = BOSSJUMP;
    m_prevStatus = BOSSJUMP;
    m_hitBox->tag = BOSS;
    m_changeTime = 6.f;
    m_curTime = 0.f;
    pos.x = -200.f;
    pos.y = float(GROUND_Y) - 246.f +40.f;
    velo.x = 0;
    velo.y = 0;
    bulletAvailable = false;
}

Boss1::~Boss1()
{
    if (m_hitBox!= NULL)
    delete m_hitBox;
    for (auto x : m_action) {
        x->~Animation();
        if (x != NULL) {
            delete x;
            x = NULL;
        }
    }    

}

void Boss1::Init(SDL_Renderer*& screen)
{
    Animation* ani;

    ani = new Animation();
    ani->Init("BossJump", 6, 3, screen);
    m_action.push_back(ani);

    ani = new Animation();
    ani->Init("BossBite", 6, 3, screen);
    m_action.push_back(ani);

    ani = new Animation();
    ani->Init("BossSkill", 6, 3, screen);
    m_action.push_back(ani);

    m_rect = { (int)pos.x,(int)pos.y,m_action[m_curStatus]->getRectSize().first,m_action[m_curStatus]->getRectSize().second };
}

void Boss1::Update(float deltaTime)
{
    if (m_curStatus == BOSSJUMP) {
        m_curTime += deltaTime;
        bulletAvailable = false;
    }
    if (m_action[m_curStatus]->checkEndFrame() == true ) {
        if (m_curStatus == BOSSSKILL) bulletAvailable = true;
        m_action[m_curStatus]->reset(); 
        ChangeStatus(BOSSJUMP); 
    }
    
    if (m_curTime > m_changeTime) {
        switch (rand() % 3) {
        case 0:
            ChangeStatus(BOSSBITE);
            break;
        case 1:
            ChangeStatus(BOSSSKILL);
            break;
        default:
            break;
        }
        m_curTime = 0.f;
    }
    m_action[m_curStatus]->Update();
    if (m_curStatus == BOSSBITE) {
        velo.x = 230.f ;
        m_action[m_curStatus]->setEndFrame(true);
        bulletAvailable = false;
    }
    else if (m_curStatus == BOSSSKILL) {
        velo.x = -50.f;
        m_action[m_curStatus]->setEndFrame(true);
    }
    else {
        velo.x = -100.f;
    }

    pos.x += velo.x * deltaTime;
    pos.y += velo.y * deltaTime;

    if (pos.x < -m_rect.w / 3 * 2) pos.x = -m_rect.w /3 *2;
    //if (pos.x < 0) pos.x = 0;
    
    if (m_curStatus == BOSSSKILL) {
        pos.y = float(GROUND_Y) - 159.f +40.f;
    }
    else pos.y = pos.y = float(GROUND_Y) - 246.f +40.f;

    m_rect.x = (int)pos.x;
    m_rect.y = (int)pos.y;
    m_rect.w = m_action[m_curStatus]->getRectSize().first;
    m_rect.h = m_action[m_curStatus]->getRectSize().second;
    m_hitBox->box.y = m_rect.y+25;
    m_hitBox->box.x = m_rect.x+50;
    m_hitBox->box.w = 230;
    m_hitBox->box.h = 180;
    if (m_curStatus == BOSSSKILL){
        m_hitBox->box.w = 130;
        m_hitBox->box.h = 100;
    }
        
}

void Boss1::ChangeStatus(int status) {
    m_prevStatus = m_curStatus;
    m_curStatus = status;
}

void Boss1::renderBoss1(SDL_Renderer*& screen)
{
    m_action[m_curStatus]->renderAni(screen, m_rect);
    //SDL_RenderDrawRect(screen, &m_hitBox->box);
}
