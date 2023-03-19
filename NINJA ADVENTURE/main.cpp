//#include "SourceGame/GameManager/ResourceManager.h"
#include "SourceGame/GameManager/CollisionManager.h"
#include "SourceGame/GameObject/ParallaxBackground.h"
#include "SourceGame/GameObject/Player.h"
#include "SourceGame/GameObject/Creep.h"
#include "SourceGame/GameObject/CreepSpawn.h"
#include "SourceGame/GameObject/Boss1.h"
#include "SourceGame/GameObject/Boss2.h"
#include "SourceGame/GameObject/BulletSpawn.h"
#include "SourceGame/GameObject/GameButton.h"
#include "SourceGame/GameManager/GameMenu.h"
#include "SourceGame/GameManager/GameEnd.h"
#include "SourceGame/GameManager/GameInfo.h"
#include "SourceGame/GameManager/GameSetting.h"
#include "SourceGame/GameManager/GameHighScore.h"

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* screen = NULL;
    SDL_Event event;
    TTF_Font* game_font = NULL;
    Mix_Chunk* menumusic = NULL;
    Mix_Chunk* defeatsound = NULL;
    Mix_Music* ingamemusic = NULL;
    GameMenu gMenu;
    GameEnd gEnd;
    GameInfo gInfo;
    GameSetting gSetting;
    GameHighScore gHighScore;

    initWorld(window, screen);
    InitResoucre();
    game_font = TTF_OpenFont("DataGame//Fonts//font.ttf", 20);
    menumusic = Mix_LoadWAV("DataGame//Musics//menu_music.mp3");
    defeatsound = Mix_LoadWAV("DataGame//Musics//end_sound.mp3");
    Mix_VolumeChunk(menumusic, 80);
    Mix_VolumeChunk(defeatsound, 80);
    gMenu.Init(screen, game_font);
    gEnd.Init(screen, game_font);
    gInfo.Init(screen, game_font);
    gSetting.Init(screen, game_font);
    gHighScore.Init(screen, game_font);

    Uint32 curTime = 0;
    Uint32 preTime = 0;
    float deltaTime = 0.f;

    bool inMenu = true;
    bool PlayAgain = true;
    bool EndGame = true;
    bool inInfo = true;
    bool inSetting = true;
    bool inHighScore = true;
    bool menumusicplayed = false;
    bool defeatsoundplayed = false;
    while (inMenu) {
        inInfo = false;
        inSetting = false;
        inHighScore = false;
        curTime = SDL_GetTicks();
        deltaTime = (float)(curTime - preTime) / 1000.f;
        preTime = curTime;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                inMenu = false;
                EndGame = false;
                PlayAgain = false;
                inInfo = false;
            }
            gMenu.Update(&event);
            if (gMenu.play_btn->isTouch == true) { inMenu = false; Mix_Pause(1); }
            if (gMenu.info_btn->isTouch == true) {
                inInfo = true;
                while (inInfo) {
                    curTime = SDL_GetTicks();
                    deltaTime = (float)(curTime - preTime) / 1000.f;
                    preTime = curTime;
                    gInfo.Update(&event);
                    SDL_RenderClear(screen);
                    gInfo.RenderInfo(screen);
                    SDL_RenderPresent(screen);
                    while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_QUIT) {
                            inInfo = false;
                            inMenu = false;
                            EndGame = false;
                            PlayAgain = false;
                        }
                        gInfo.Update(&event);
                        if (gInfo.back_btn->isTouch == true) {
                            inInfo = false;
                        }
                    }
                }
            }
            if (gMenu.setting_btn->isTouch == true) {
                inSetting = true;
                while (inSetting) {
                    curTime = SDL_GetTicks();
                    deltaTime = (float)(curTime - preTime) / 1000.f;
                    preTime = curTime;
                    gSetting.Update(&event);
                    SDL_RenderClear(screen);
                    gSetting.RenderSetting(screen);
                    SDL_RenderPresent(screen);
                    while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_QUIT) {
                            inSetting = false;
                            inMenu = false;
                            EndGame = false;
                            PlayAgain = false;
                        }
                        gSetting.Update(&event);
                        if (gSetting.back_btn->isTouch == true) {
                            inSetting = false;
                        }
                    }
                }
            }
            if (gMenu.highscore_btn->isTouch == true) {
                inHighScore = true;
                while (inHighScore) {
                    curTime = SDL_GetTicks();
                    deltaTime = (float)(curTime - preTime) / 1000.f;
                    preTime = curTime;
                    gSetting.Update(&event);
                    SDL_RenderClear(screen);
                    gSetting.RenderSetting(screen);
                    SDL_RenderPresent(screen);
                    while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_QUIT) {
                            inHighScore = false;
                            inMenu = false;
                            EndGame = false;
                            PlayAgain = false;
                        }
                        gSetting.Update(&event);
                        if (gSetting.back_btn->isTouch == true) {
                            inHighScore = false;
                        }
                    }
                }
            }
            if (gMenu.exit_btn->isTouch == true) { inMenu = false; PlayAgain = false; EndGame = false; }
            
        }
            if (menumusicplayed == false)
            {
                Mix_PlayChannel(1, menumusic, -1); menumusicplayed = true;
            }
        
            SDL_RenderClear(screen);
            gMenu.Update(&event);
            gMenu.RenderMenu(screen);
            SDL_Delay(25);
            SDL_RenderPresent(screen);
        
    }

    while (PlayAgain) {
        EndGame = true;
        defeatsoundplayed = false;
        ParallaxBG bkground;
        Player player;
        Collision interactObj;
        CreepManager creepmanager;
        Boss1 boss1;
        Boss2 boss2;
        BulletManager bulletmanager;

        //Init
        bkground.Init(screen);
        player.Init(screen, game_font);
        boss1.Init(screen);
        boss2.Init(screen);
        creepmanager.Init(interactObj, screen);
        bulletmanager.Init(interactObj, screen);

        ingamemusic = Mix_LoadMUS("DataGame//Musics//Victory.mp3");
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
        Mix_VolumeMusic(60);
        Mix_VolumeChunk(playersound[8], 14);
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

        float cooldownTime = 0.f;
        float spawnboss1time = 0.f;
        float spawnboss2time = 0.f;
        float waitingtime = 7.f;
        bool boss1spawn = false;
        float score_val = 0.f;
        bool death_sound = false;
        bool isDecrease = true; // giam thoi gian hoi chieu cua boss

        bool is_quit = false;
        while (!is_quit) {

            curTime = SDL_GetTicks();
            deltaTime = (float)(curTime - preTime) / 1000.f;
            preTime = curTime;
            if (player.skillAvailable == false) cooldownTime += deltaTime;
            if (cooldownTime > COOLDOWN_SKILL) {
                player.skillAvailable = true;
                cooldownTime = 0;
            }

            if (spawnboss1time < BOSS1SPAWNTIME && boss1spawn == false && player.getHitBox()->isAlive == true) spawnboss1time += deltaTime;
            else if (spawnboss1time < BOSS1SPAWNTIME && boss1spawn == false && player.getHitBox()->isAlive == false) spawnboss1time += 0;
            else
            {
                boss1spawn = true; spawnboss1time = 0;
            }

            if (spawnboss2time < BOSS2SPAWNTIME && boss2.boss2spawn == false && player.getHitBox()->isAlive == true) spawnboss2time += deltaTime;
            else if (spawnboss2time < BOSS2SPAWNTIME && boss2.boss2spawn == false && player.getHitBox()->isAlive == false) spawnboss2time += 0;
            else { boss2.boss2spawn = true; spawnboss2time = 0; }

            if (player.getHitBox()->isAlive == true) score_val += deltaTime;

            if (player.getHitBox()->isAlive == false && player.getHitBox()->lives <= 0 && death_sound == false) {
                Mix_PlayChannel(-1, playersound[6], 0);
                Mix_PlayChannel(-1, playersound[7], 0); death_sound = true;
            }
            if (player.getHitBox()->isAlive == false && player.getHitBox()->lives > 0 && death_sound == false) {
                Mix_PlayChannel(-1, playersound[6], 0); death_sound = true;
            }
            if (Mix_PlayingMusic() == 0) {
                Mix_PlayMusic(ingamemusic, -1);
            }
            if (player.getHitBox()->isAlive == false && Mix_PausedMusic() == 0) Mix_PauseMusic();
            if (player.getHitBox()->isAlive == true && Mix_PausedMusic() == 1) Mix_ResumeMusic();

            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    is_quit = true;
                    EndGame = false;
                    PlayAgain = false;
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
            //Update
            player.Update(deltaTime);
            if (player.getHitBox()->isAlive == true) {
                bkground.Update();
                creepmanager.Update(deltaTime);
                if (boss1spawn == true) boss1.Update(deltaTime);
                if (boss2.boss2spawn == true) boss2.Update(deltaTime);
                death_sound = false;
            }
            bulletmanager.Update(deltaTime, &player, &boss1, &boss2, playersound);
            interactObj.Update();
            if ((int)score_val % 40) {
                if (isDecrease) {
                    if (score_val >= 80) boss1.m_changeTime -= 1.f;
                    if (score_val >= 100) boss2.m_skillTime -= 1.f;
                    isDecrease = false;
                }
            }
            else isDecrease = true;

            score_text = std::to_string((int)score_val);
            scoregame->setText("Score: " + score_text);
            scoregame->LoadText(game_font, screen);

            nofi_respawn->setText("Press R to respawn");
            nofi_respawn->LoadText(game_font, screen);
            nofi_respawn->setPos(player.getHitBox()->box.x - 30, player.getHitBox()->box.y - 20);
            nofi_respawn->setSize(150, 15);
            //Render
            bkground.RenderBG(screen, &boss2);
            scoregame->RenderText(screen);
            player.renderPlayer(screen);
            creepmanager.renderManyCreep(screen);
            boss1.renderBoss1(screen);
            bulletmanager.renderBullet(screen);

            if (player.getHitBox()->isAlive == false && player.getHitBox()->lives > 0) {
                nofi_respawn->RenderText(screen);
                nofi_respawn->setColor(colorkey[countcolor / 10]);
                countcolor += 2;
                if (countcolor > 80) countcolor = 0;
            }
            SDL_RenderPresent(screen);

            if (1000 / FPS > deltaTime)
                SDL_Delay((1000 / FPS) - deltaTime);

            if (player.getHitBox()->isAlive == false && player.getHitBox()->lives <= 0) {
                waitingtime -= deltaTime;
                if (waitingtime < 0) {
                    is_quit = true;
                    for (int i = 0; i < 9; i++) {
                        Mix_FreeChunk(playersound[i]);
                    }
                    Mix_FreeMusic(ingamemusic);
                    delete nofi_respawn;
                    delete scoregame;
                }
            }
            std::cout << deltaTime << std::endl;
        }
        while (EndGame) {

            curTime = SDL_GetTicks();
            deltaTime = (float)(curTime - preTime) / 1000.f;
            preTime = curTime;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    EndGame = false;
                    PlayAgain = false;
                }
                gEnd.Update(&event);
                SDL_RenderClear(screen);
                gEnd.RenderEnd(screen);
                SDL_RenderPresent(screen);
                if (defeatsoundplayed == false) {
                    Mix_PlayChannel(-1, defeatsound, 0);
                    defeatsoundplayed = true;
                }
                if (gEnd.again_btn->isTouch == true) EndGame = false;
                if (gEnd.home_btn->isTouch == true) {
                    inMenu = true;
                }
                while (inMenu) {
                    curTime = SDL_GetTicks();
                    deltaTime = (float)(curTime - preTime) / 1000.f;
                    preTime = curTime;
                    gMenu.Update(&event);
                    SDL_RenderClear(screen);
                    gMenu.RenderMenu(screen);
                    SDL_Delay(25);
                    SDL_RenderPresent(screen);
                    Mix_Resume(1);
                    while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_QUIT) {
                            inMenu = false;
                            EndGame = false;
                            PlayAgain = false;
                        }
                        gMenu.Update(&event);
                        if (gMenu.play_btn->isTouch == true) {
                            inMenu = false; EndGame = false; Mix_Pause(1);
                        }
                        if (gMenu.info_btn->isTouch == true) {
                            inInfo = true;
                            while (inInfo) {
                                curTime = SDL_GetTicks();
                                deltaTime = (float)(curTime - preTime) / 1000.f;
                                preTime = curTime;
                                gInfo.Update(&event);
                                SDL_RenderClear(screen);
                                gInfo.RenderInfo(screen);
                                SDL_RenderPresent(screen);
                                while (SDL_PollEvent(&event)) {
                                    if (event.type == SDL_QUIT) {
                                        inInfo = false;
                                        inMenu = false;
                                        EndGame = false;
                                        PlayAgain = false;
                                    }
                                    gInfo.Update(&event);
                                    if (gInfo.back_btn->isTouch == true) {
                                        inInfo = false;
                                    }
                                }
                            }
                        }
                        if (gMenu.setting_btn->isTouch == true) {
                            inSetting = true;
                            while (inSetting) {
                                curTime = SDL_GetTicks();
                                deltaTime = (float)(curTime - preTime) / 1000.f;
                                preTime = curTime;
                                gSetting.Update(&event);
                                SDL_RenderClear(screen);
                                gSetting.RenderSetting(screen);
                                SDL_RenderPresent(screen);
                                while (SDL_PollEvent(&event)) {
                                    if (event.type == SDL_QUIT) {
                                        inSetting = false;
                                        inMenu = false;
                                        EndGame = false;
                                        PlayAgain = false;
                                    }
                                    gSetting.Update(&event);
                                    if (gSetting.back_btn->isTouch == true) {
                                        inSetting = false;
                                    }
                                }
                            }
                        }
                        if (gMenu.highscore_btn->isTouch == true) {
                            inHighScore = true;
                            while (inHighScore) {
                                curTime = SDL_GetTicks();
                                deltaTime = (float)(curTime - preTime) / 1000.f;
                                preTime = curTime;
                                gSetting.Update(&event);
                                SDL_RenderClear(screen);
                                gSetting.RenderSetting(screen);
                                SDL_RenderPresent(screen);
                                while (SDL_PollEvent(&event)) {
                                    if (event.type == SDL_QUIT) {
                                        inHighScore = false;
                                        inMenu = false;
                                        EndGame = false;
                                        PlayAgain = false;
                                    }
                                    gSetting.Update(&event);
                                    if (gSetting.back_btn->isTouch == true) {
                                        inHighScore = false;
                                    }
                                }
                            }
                        }
                        if (gMenu.exit_btn->isTouch == true) { inMenu = false; PlayAgain = false; EndGame = false; }
                    }

                }
            }
        }
    }
    close(window, screen);
    return 0;
}


