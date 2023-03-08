#include "Player.h"

Player::Player()
{
    m_hitBox = new HitBox();
    protectBox = new HitBox();
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
    protectBox->tag = PROTECT;
    protectBox->box = { 0,0,96,96 };
    protectBox->isAlive = false;
    m_hitBox->tag=PLAYER;
    m_hitBox->isAlive = true;
    m_hitBox->haveProtect = false;
    m_hitBox->box = { 0,0,30,50 };
    m_hitBox->lives = 6;
    skillslot = { 0, 50, 64,64 };
    liveslot = { 0,0,144, 48 };
    protectTime = PROTECTTIME;
    
}

Player::~Player()
{
}

void Player::Init(SDL_Renderer* &screen,TTF_Font* font)
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

    ImgSkillAvailable = new Animation();
    ImgSkillCooldown = new Animation();
    ImgSkillAvailable->Init("SkillAvailable", 4, 1, screen);
    ImgSkillCooldown->Init("SkillCooldown", 1, 1, screen);
    protect = new Animation();
    protect->Init("EnergyCircle", 4, 1, screen);

    SDL_Texture* tmp = NULL;
    tmp = IMG_LoadTexture(screen, m_mapTexture["Health0"].c_str());
    lives.push_back(tmp);
    tmp = IMG_LoadTexture(screen, m_mapTexture["Health1"].c_str());
    lives.push_back(tmp);
    tmp = IMG_LoadTexture(screen, m_mapTexture["Health2"].c_str());
    lives.push_back(tmp);
    tmp = IMG_LoadTexture(screen, m_mapTexture["Health3"].c_str());
    lives.push_back(tmp);
    tmp = IMG_LoadTexture(screen, m_mapTexture["Health4"].c_str());
    lives.push_back(tmp);
    tmp = IMG_LoadTexture(screen, m_mapTexture["Health5"].c_str());
    lives.push_back(tmp);
    tmp = IMG_LoadTexture(screen, m_mapTexture["Health6"].c_str());
    lives.push_back(tmp);
    
    m_rect = { (int)pos.x,(int)pos.y,m_action[m_curStatus]->getRectSize().first,m_action[m_curStatus]->getRectSize().second };
}

void Player::InputAction()
{
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    velo.x = 0.f;
    if (keystates[SDL_SCANCODE_R] && m_hitBox->lives > 0 && m_curStatus == DEATH) { 
        m_hitBox->isAlive = true; 
        ChangeStatus(RUN); 
        m_hitBox->haveProtect = true; 
        protectTime = PROTECTTIME;
        protectBox->isAlive = true;
    }
    if (m_hitBox->isAlive != false) {
        if (keystates[SDL_SCANCODE_D]) { velo.x += move.x; }
        if (keystates[SDL_SCANCODE_A]) { velo.x -= move.x; }
        if (keystates[SDL_SCANCODE_W]) { velo.y -= move.y; }
        if (keystates[SDL_SCANCODE_SPACE] && skillAvailable == true) { useSkill = true; }
    }

}

void Player::Update(float deltaTime)
{
    if (m_hitBox->haveProtect == true) {
        protectTime -= deltaTime;
        protect->Update();
    }
    if (protectTime < 0) { m_hitBox->haveProtect = false; protectBox->isAlive = false; }
    if (m_hitBox->isAlive == false) {
        ChangeStatus(DEATH); 
        m_action[m_curStatus]->setEndFrame(true);
        m_action[m_curStatus]->slowFrame(8);
    }
    if (velo.y > 0.f && m_curStatus == JUMP ) ChangeStatus(FALL);
    if (pos.y + m_rect.h < GROUND_Y && velo.y < 0.f) ChangeStatus(JUMP);
    if (useSkill == true) {
        ChangeStatus(ATTACK); 
    }
    m_action[m_curStatus]->Update();

    if (skillAvailable == true) ImgSkillAvailable->Update();
    else ImgSkillCooldown->Update();


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
    if (pos.x < 0) pos.x = 0;
    if (pos.x + m_rect.w > SCREEN_WIDTH) pos.x = SCREEN_WIDTH - m_rect.w;

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
    pos_protect = { m_rect.x-20, m_rect.y-20,96,96 };
    m_hitBox->box.y = m_rect.y;
    m_hitBox->box.x = m_rect.x + 15;
    protectBox->box.x = pos_protect.x;
    protectBox->box.y = pos_protect.y;
    if (m_curStatus == FALL)
        m_hitBox->box.w = 30;
    else if (m_curStatus == JUMP)
        m_hitBox->box.w = 20;

}

void Player::ChangeStatus(int status) {
    m_prevStatus = m_curStatus;    
    m_curStatus = status;
}

void Player::renderPlayer(SDL_Renderer*& screen)
{
    //if (m_curStatus == ATTACK) { useSkill = false; skillAvailable = false; }
    if (skillAvailable == true) ImgSkillAvailable->renderAni(screen, skillslot);
    else ImgSkillCooldown->renderAni(screen, skillslot);
    if (m_hitBox->haveProtect == true) protect->renderAni(screen, pos_protect);
    m_action[m_curStatus]->renderAni(screen, m_rect);
    SDL_RenderCopy(screen, lives[m_hitBox->lives], NULL, &liveslot);
    //SDL_RenderDrawRect(screen, &protectBox->box);
}
