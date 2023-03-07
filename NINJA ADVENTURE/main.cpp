#include "SourceGame/GameManager/ResourceManager.h"
#include "SourceGame/GameManager/CollisionManager.h"
#include "SourceGame/GameObject/ParallaxBackground.h"
#include "SourceGame/GameObject/Player.h"
#include "SourceGame/GameObject/Creep.h"
#include "SourceGame/GameObject/CreepSpawn.h"
#include "SourceGame/GameObject/Boss1.h"
#include "SourceGame/GameObject/Boss2.h"
#include "SourceGame/GameObject/BulletSpawn.h"
#include "SourceGame/GameObject/Text.h"

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* screen = NULL;
    SDL_Event event;
    TTF_Font* font;
    Mix_Music* ingamemusic = NULL;
    Mix_Music* menumusic = NULL;

    initWorld(window, screen);
    InitResoucre();
    

    ParallaxBG bkground;
    Player player;
    Collision interactObj;
    CreepManager creepmanager;
    Boss1 boss1;
    Boss2 boss2;
    BulletManager bulletmanager;


    bkground.Init(screen);
    player.Init(screen);
    boss1.Init(screen);
    boss2.Init(screen);
    creepmanager.Init(interactObj, screen);
    bulletmanager.Init(interactObj, screen);
    ingamemusic = Mix_LoadMUS("DataGame//Musics//lofichill.mp3");
    if (ingamemusic == NULL) std::cout << "aaa";
    interactObj.addObj(player.getHitBox());
    interactObj.addObj(boss1.getHitBox());
    interactObj.addObj(player.getProtectBox());  

    font = TTF_OpenFont("DataGame//Fonts//font.ttf", 20);
    Text* scoregame = new Text();
    std::string score_text = "";
    scoregame->setPos(SCREEN_WIDTH / 2 - 100, 0);
    scoregame->setColor(WHITE_COLOR);
    
    Uint32 curTime = 0;
    Uint32 preTime = 0;
    float deltaTime = 0.f;
    float cooldownTime = 0.f;
    float spawnboss1time = 0.f;
    float spawnboss2time = 0.f;
    bool boss1spawn=false;
    float score_val = 0.f;

    bool is_quit = false;
    while (!is_quit) {

        curTime = SDL_GetTicks();
        deltaTime = (float)(curTime - preTime) / 1000.f;
        preTime = curTime;
        if (player.skillAvailable==false) cooldownTime += deltaTime;
        if (cooldownTime > COOLDOWN_SKILL) { 
            //std::cout << "SKILL AVAILABLE" << std::endl; 
            player.skillAvailable = true;
            cooldownTime = 0;
        }

        if (spawnboss1time < BOSS1SPAWNTIME && boss1spawn == false && player.getHitBox()->isAlive == true) spawnboss1time += deltaTime;
        else if (spawnboss1time < BOSS1SPAWNTIME && boss1spawn == false && player.getHitBox()->isAlive == false) spawnboss1time += 0;
        else
        { boss1spawn = true; spawnboss1time = 0; }

        if (spawnboss2time < BOSS2SPAWNTIME && boss2.boss2spawn == false && player.getHitBox()->isAlive == true) spawnboss2time += deltaTime;
        else if (spawnboss2time < BOSS2SPAWNTIME && boss2.boss2spawn == false && player.getHitBox()->isAlive == false) spawnboss2time += 0;
        else { boss2.boss2spawn = true; spawnboss2time = 0; }

        if(player.getHitBox()->isAlive== true) score_val += deltaTime;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                is_quit = true;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                is_quit = true;
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_m)
                if (Mix_PlayingMusic() == 0)
            {
                Mix_PlayMusic(ingamemusic, -1);
            }
            else
            {
                if (Mix_PausedMusic() == 1)
                {
                    Mix_ResumeMusic();
                }
                else
                {
                    Mix_PauseMusic();
                }   
            }
        }
        
        player.InputAction();
        SDL_RenderClear(screen);
        SDL_SetRenderDrawColor(screen, 255, 255, 255, 255);

        player.Update(deltaTime);
        if (player.getHitBox()->isAlive == true) {
            bkground.Update();            
            creepmanager.Update(deltaTime);
            if (boss1spawn == true) boss1.Update(deltaTime);
            if (boss2.boss2spawn==true) boss2.Update(deltaTime);           
        }
        
        bulletmanager.Update(deltaTime, &player, &boss1,&boss2);
        interactObj.Update();

        score_text = std::to_string((int)score_val);
        scoregame->setText("Score: " + score_text);
        scoregame->LoadText(font, screen);


        bkground.RenderBG(screen,&boss2);
        scoregame->RenderText(screen);
        player.renderPlayer(screen);
        creepmanager.renderManyCreep(screen);
        boss1.renderBoss1(screen);
        bulletmanager.renderBullet(screen);
        SDL_RenderPresent(screen);

        if (1000 / FPS > deltaTime)
            SDL_Delay((1000 / FPS) - deltaTime);
    }
    close(window, screen);
    return 0;
}

