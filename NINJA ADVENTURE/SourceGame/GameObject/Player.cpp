#include "Player.h"

Player::Player()
{
    m_hitBox = new HitBox();
    m_curStatus = RUN;
    m_prevStatus = RUN;
    pos.x = 200.f;
    pos.y = 400.f;
    velo.x = 0.f;
    velo.y = 300.f;
    move.x = 100.f;
    move.y = 100.f;
    skillAvailable = true;
    useSkill = false;
    m_hitBox->tag=PLAYER;
    m_hitBox->isAlive = true;
    m_hitBox->box = { 0,0,30,50 };
}

Player::~Player()
{
}

void Player::Init(SDL_Renderer* &screen)
{
    Animation* ani;

    ani = new Animation();
    ani->Init("Run", 8, 1, screen);
    m_action.push_back(ani);

    ani = new Animation();
    ani->Init("Jump", 2, 1, screen);
    m_action.push_back(ani);

    ani = new Animation();
    ani->Init("Fall", 2, 1, screen);
    m_action.push_back(ani);

    ani = new Animation();
    ani->Init("Attack", 1, 1, screen);
    m_action.push_back(ani);

    ani = new Animation();
    ani->Init("Death", 4, 1, screen);
    m_action.push_back(ani);
    
    m_rect = { (int)pos.x,(int)pos.y,m_action[m_curStatus]->getRectSize().first,m_action[m_curStatus]->getRectSize().second };
}

void Player::InputAction()
{
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    velo.x = 0.f;
    if (keystates[SDL_SCANCODE_R]) { m_hitBox->isAlive = true; ChangeStatus(RUN); }
    if (m_hitBox->isAlive != false) {
        if (keystates[SDL_SCANCODE_RIGHT]) { velo.x += move.x; }
        if (keystates[SDL_SCANCODE_LEFT]) { velo.x -= move.x; }
        if (keystates[SDL_SCANCODE_UP]) { velo.y -= move.y; }
        if (keystates[SDL_SCANCODE_SPACE] && skillAvailable == true) { useSkill = true; }
    }

}

void Player::Update(float deltaTime)
{
    if (m_hitBox->isAlive == false) {
        ChangeStatus(DEATH); 
        m_action[m_curStatus]->setEndFrame(true);
        m_action[m_curStatus]->slowFrame(8);
    }
    if (velo.y > 0.f && m_curStatus == JUMP ) ChangeStatus(FALL);
    if (pos.y + m_rect.h < GROUND_Y && velo.y < 0.f) ChangeStatus(JUMP);
    if (useSkill == true) ChangeStatus(ATTACK);
    m_action[m_curStatus]->Update();


    velo.y += GRAVITY;
    if (m_curStatus == FALL) {
        velo.x += move.x / 4;
    }
    if (m_curStatus == DEATH) {
        velo.x = 0;
    }


    //update position
    pos.x += velo.x*deltaTime;
    pos.y += velo.y*deltaTime;

    //check ground
    if (pos.y + m_rect.h > GROUND_Y) {
        pos.y = GROUND_Y - m_rect.h;
        velo.y = 0.f;
        if (m_curStatus != DEATH) {
            if (m_curStatus == FALL) ChangeStatus(RUN);
            if (useSkill == false) ChangeStatus(RUN);
        }
    }

    //check max height
    if (pos.y <= 0) pos.y = 0;
    if (pos.y <= MAX_HEIGHT) {
        velo.y +=100.f;
    }

    //update m_rect
    m_rect.x = (int)pos.x;
    m_rect.y = (int)pos.y;
    m_rect.w = m_action[m_curStatus]->getRectSize().first;
    m_rect.h = m_action[m_curStatus]->getRectSize().second;
    m_hitBox->box.y = m_rect.y;
    m_hitBox->box.x = m_rect.x + 15;
    if (m_curStatus == FALL)
        m_hitBox->box.w = 30;
    else if (m_curStatus == JUMP)
        m_hitBox->box.w = 20;
}

void Player::ChangeStatus(int status) {
    m_prevStatus = m_curStatus;    
    m_curStatus = status;
}

void Player::renderPlayer(SDL_Renderer* &screen)
{
    if (m_curStatus == ATTACK) { useSkill = false; skillAvailable = false; }
    m_action[m_curStatus]->renderAni(screen, m_rect);
    //SDL_RenderDrawRect(screen, &m_hitBox->box);
}
