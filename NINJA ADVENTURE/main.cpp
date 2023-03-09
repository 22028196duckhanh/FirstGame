﻿#include "SourceGame/GameManager/ResourceManager.h"
#include "SourceGame/GameManager/CollisionManager.h"
#include "SourceGame/GameObject/ParallaxBackground.h"
#include "SourceGame/GameObject/Player.h"
#include "SourceGame/GameObject/Creep.h"
#include "SourceGame/GameObject/CreepSpawn.h"
#include "SourceGame/GameObject/Boss1.h"
#include "SourceGame/GameObject/Boss2.h"
#include "SourceGame/GameObject/BulletSpawn.h"

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* screen = NULL;
    SDL_Event event;
    TTF_Font* game_font = NULL; 
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

    game_font = TTF_OpenFont("DataGame//Fonts//font.ttf", 20);
    bkground.Init(screen);
    player.Init(screen,game_font);
    boss1.Init(screen);
    boss2.Init(screen);
    creepmanager.Init(interactObj, screen);
    bulletmanager.Init(interactObj, screen);

    ingamemusic = Mix_LoadMUS("DataGame//Musics//Victory.mp3");
    //if (ingamemusic == NULL) std::cout << "aaa";
    Mix_Chunk* playersound[9] = {
        Mix_LoadWAV("DataGame//Musics//yasuo_son.mp3"),       
        Mix_LoadWAV("DataGame//Musics//yasuo_choryon.mp3"),
        Mix_LoadWAV("DataGame//Musics//yasuo_aseryo.mp3"),
        Mix_LoadWAV("DataGame//Musics//yasuo_hasagi.mp3"),        
        Mix_LoadWAV("DataGame//Musics//yasuo_facethewind.mp3"),
        Mix_LoadWAV("DataGame//Musics//yasuo_ton.mp3"),
        Mix_LoadWAV("DataGame//Musics//yasuo_death.mp3"),
        Mix_LoadWAV("DataGame//Musics//death_is_like_a_wind.mp3"),
        Mix_LoadWAV("DataGame//Musics//Boss2SkillSound.mp3")
    };
    Mix_VolumeChunk(playersound[8], 20);
    Mix_VolumeChunk(playersound[7], 100);

    interactObj.addObj(player.getHitBox());
    interactObj.addObj(boss1.getHitBox());
    interactObj.addObj(player.getProtectBox());  

    Text* scoregame = new Text();
    std::string score_text = "";
    scoregame->setPos(SCREEN_WIDTH / 2 - 100, 0);
    scoregame->setColor(WHITE_COLOR);

    Text* nofi_respawn = new Text();
    nofi_respawn->setColor(WHITE_COLOR);
    int countcolor = 0;
    
    Uint32 curTime = 0;
    Uint32 preTime = 0;
    float deltaTime = 0.f;
    float cooldownTime = 0.f;
    float spawnboss1time = 0.f;
    float spawnboss2time = 0.f;
    float waitingtime = 7.f;
    bool boss1spawn=false;
    float score_val = 0.f;
    bool death_sound = false;


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

        if (player.getHitBox()->isAlive == false && player.getHitBox()->lives <= 0 && death_sound == false) {
            Mix_PlayChannel(-1, playersound[6], 0);
            Mix_PlayChannel(-1, playersound[7], 0); death_sound = true;
        }
        if (player.getHitBox()->isAlive == false && player.getHitBox()->lives > 0 && death_sound == false) {
            Mix_PlayChannel(-1, playersound[6], 0); death_sound = true;
        }
        Mix_VolumeMusic(60);
        if (Mix_PlayingMusic() == 0)
        {
            Mix_PlayMusic(ingamemusic, -1);
        }
        if (player.getHitBox()->isAlive == false && Mix_PausedMusic() == 0) Mix_PauseMusic();
        if (player.getHitBox()->isAlive == true && Mix_PausedMusic() == 1) Mix_ResumeMusic();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                is_quit = true;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                is_quit = true;
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_m) 
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
            death_sound = false;
        }    
        bulletmanager.Update(deltaTime, &player, &boss1,&boss2,playersound);
        interactObj.Update();

        score_text = std::to_string((int)score_val);
        scoregame->setText("Score: " + score_text);
        scoregame->LoadText(game_font, screen);
        
        nofi_respawn->setText("Press R to respawn");
        nofi_respawn->LoadText(game_font, screen);        
        nofi_respawn->setPos(player.getHitBox()->box.x-30, player.getHitBox()->box.y-20);
        nofi_respawn->setSize(150, 15);
        
        bkground.RenderBG(screen,&boss2);
        scoregame->RenderText(screen);
        player.renderPlayer(screen);
        creepmanager.renderManyCreep(screen);
        boss1.renderBoss1(screen);
        bulletmanager.renderBullet(screen);
        
        if (player.getHitBox()->isAlive == false && player.getHitBox()->lives>0) {
            nofi_respawn->RenderText(screen);
            nofi_respawn->setColor(colorkey[countcolor / 10]);
            countcolor+=2;
            if (countcolor > 80) countcolor = 0;
        }
        SDL_RenderPresent(screen);

        if (1000 / FPS > deltaTime)
            SDL_Delay((1000 / FPS) - deltaTime);

        if (player.getHitBox()->isAlive == false && player.getHitBox()->lives <= 0) {
            waitingtime -= deltaTime;
            if (waitingtime < 0) is_quit = true;
        }
    }
    close(window, screen);
    return 0;
}

