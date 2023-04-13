#include "SourceGame/GameManager/ResourceManager.h"
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
#include "SourceGame/GameManager/GamePause.h"

int main(int argc, char* argv[]) {

    SDL_Window* window = NULL;
    SDL_Renderer* screen = NULL;
    SDL_Event event;
    TTF_Font* game_font = NULL;
    Mix_Chunk* menumusic = NULL;
    Mix_Chunk* defeatsound = NULL;
    Mix_Music* ingamemusic = NULL;
    Mix_Chunk* click_sound = NULL;
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
    click_sound = Mix_LoadWAV("DataGame//Musics//click_sound.mp3");
    gMenu.Init(screen, game_font);
    gEnd.Init(screen, game_font);
    gInfo.Init(screen, game_font);
    gSetting.Init(screen, game_font);
    gHighScore.Init(screen, game_font);
    Mix_VolumeChunk(menumusic, volume_unit*gSetting.power);
    Mix_VolumeChunk(defeatsound, volume_unit * gSetting.power);
    Mix_VolumeChunk(click_sound, volume_unit * gSetting.power/3);

    Uint32 curTime = 0;
    Uint32 preTime = 0;
    float deltaTime = 0.f;

    bool inMenu = true;
    bool PlayAgain = true;
    bool EndGame = true;
    bool inInfo = true;
    bool inSetting = true;
    bool inHighScore = true;
    bool inPause = true;
    bool pausetohome = true;
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
            if (gMenu.play_btn->isTouch == true) { inMenu = false; Mix_Pause(1); Mix_PlayChannel(-1, click_sound, 0); }
            if (gMenu.info_btn->isTouch == true) {
                Mix_PlayChannel(-1, click_sound, 0);
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
                Mix_PlayChannel(-1, click_sound, 0);
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
                Mix_VolumeChunk(menumusic, volume_unit * gSetting.power);
                Mix_VolumeChunk(defeatsound, volume_unit * gSetting.power);
                Mix_VolumeChunk(click_sound, volume_unit * gSetting.power / 3);
            }
            if (gMenu.highscore_btn->isTouch == true) {
                Mix_PlayChannel(-1, click_sound, 0);
                inHighScore = true;
                while (inHighScore) {
                    curTime = SDL_GetTicks();
                    deltaTime = (float)(curTime - preTime) / 1000.f;
                    preTime = curTime;
                    gHighScore.Update(&event,game_font,screen);
                    SDL_RenderClear(screen);
                    gHighScore.RenderHighScore(screen);
                    SDL_RenderPresent(screen);
                    while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_QUIT) {
                            inHighScore = false;
                            inMenu = false;
                            EndGame = false;
                            PlayAgain = false;
                        }
                        gHighScore.Update(&event, game_font, screen);
                        if (gHighScore.back_btn->isTouch == true) {
                            inHighScore = false;
                        }
                    }
                }
            }
            if (gMenu.exit_btn->isTouch == true) { inMenu = false; PlayAgain = false; EndGame = false; Mix_PlayChannel(-1, click_sound, 0);}
            
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
    //GamePlay
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
        Button pause;
        GamePause gPause;

        //Init
        bkground.Init(screen);
        player.Init(screen, game_font);
        boss1.Init(screen);
        boss2.Init(screen);
        creepmanager.Init(interactObj, screen);
        bulletmanager.Init(interactObj, screen);
        gPause.Init(screen, game_font);
        pause.Init(screen, "Pause", 0);
        pause.setPos(SCREEN_WIDTH - 76,0);

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
        Mix_VolumeMusic(volume_unit* gSetting.power);
        Mix_VolumeChunk(playersound[8], volume_unit* gSetting.power/6);
        Mix_VolumeChunk(playersound[7], volume_unit* gSetting.power);

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

        //gameloop
        bool is_quit = false;
        while (!is_quit) {
            inPause = false;
            pausetohome = false;
            curTime = SDL_GetTicks();
            deltaTime = (float)(curTime - preTime) / 1000.f;
            preTime = curTime;
            if (player.skillAvailable == false) cooldownTime += deltaTime;
            if (cooldownTime > COOLDOWN_SKILL) {
                player.skillAvailable = true;
                cooldownTime = 0;
            }
            // quan li thoi gian boss ra
            if (spawnboss1time < BOSS1SPAWNTIME && boss1spawn == false && player.getHitBox()->isAlive == true) spawnboss1time += deltaTime;
            else if (spawnboss1time < BOSS1SPAWNTIME && boss1spawn == false && player.getHitBox()->isAlive == false) spawnboss1time += 0;
            else
            {
                boss1spawn = true; spawnboss1time = 0;
            }

            if (spawnboss2time < BOSS2SPAWNTIME && boss2.boss2spawn == false && player.getHitBox()->isAlive == true) spawnboss2time += deltaTime;
            else if (spawnboss2time < BOSS2SPAWNTIME && boss2.boss2spawn == false && player.getHitBox()->isAlive == false) spawnboss2time += 0;
            else { boss2.boss2spawn = true; spawnboss2time = 0; }
            // diem tang theo thoi gian
            if (player.getHitBox()->isAlive == true) score_val += deltaTime;
            //am thanh va cham
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
                pause.Update(&event);
                //GamePause
                if (pause.isTouch == true) {
                    inPause = true;
                    Mix_PauseMusic(); Mix_PlayChannel(-1, click_sound, 0);
                }
                while (inPause) {
                    curTime = SDL_GetTicks();
                    deltaTime = (float)(curTime - preTime) / 1000.f;
                    preTime = curTime;
                    gPause.Update(&event);
                    SDL_RenderClear(screen);
                    bkground.RenderBG(screen, &boss2);
                    scoregame->RenderText(screen);
                    player.renderPlayer(screen);
                    creepmanager.renderManyCreep(screen);
                    boss1.renderBoss1(screen);
                    bulletmanager.renderBullet(screen);
                    gPause.RenderPause(screen);
                    SDL_RenderPresent(screen);
                    while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_QUIT) {
                            inSetting = false;
                            inMenu = false;
                            EndGame = false;
                            PlayAgain = false;
                            inPause = false;
                            break;
                        }
                        gPause.Update(&event);
                        if (gPause.resume_btn->isTouch == true) {
                            inPause = false;
                            Mix_ResumeMusic();
                            break;
                        }
                        if (gPause.home_btn->isTouch == true) {
                            Mix_PlayChannel(-1, click_sound, 0);
                            inPause = false;
                            pausetohome = true;
                            is_quit = true;
                            inMenu = true;
                            for (int i = 0; i < 9; i++) {
                                Mix_FreeChunk(playersound[i]);
                            }
                            Mix_FreeMusic(ingamemusic);
                            delete nofi_respawn;
                            delete scoregame;
                            break;
                        }
                    }
                }
                if (pausetohome) break;
                if (waitingtime < 0) break;
            }
            if (!pausetohome) {
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

                pause.Update(&event);
                //Render
                bkground.RenderBG(screen, &boss2);
                scoregame->RenderText(screen);
                player.renderPlayer(screen);
                creepmanager.renderManyCreep(screen);
                boss1.renderBoss1(screen);
                bulletmanager.renderBullet(screen);
                pause.RenderButton(screen);

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
                    waitingtime -= deltaTime * 2;
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
            }
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
                if (!pausetohome) {
                    gEnd.Update(&event,screen,game_font,score_val);
                    SDL_RenderClear(screen);
                    gEnd.RenderEnd(screen);
                    SDL_RenderPresent(screen);
                    if (defeatsoundplayed == false) {
                        Mix_PlayChannel(-1, defeatsound, 0);
                        defeatsoundplayed = true;
                    }
                    if (gEnd.again_btn->isTouch == true) { EndGame = false; Mix_PlayChannel(-1, click_sound, 0);}
                    if (gEnd.home_btn->isTouch == true) {
                        Mix_PlayChannel(-1, click_sound, 0);
                        inMenu = true;
                    }
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
                            Mix_PlayChannel(-1, click_sound, 0);
                        }
                        if (gMenu.info_btn->isTouch == true) {
                            Mix_PlayChannel(-1, click_sound, 0);
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
                            Mix_PlayChannel(-1, click_sound, 0);
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
                            Mix_VolumeChunk(menumusic, volume_unit* gSetting.power);
                            Mix_VolumeChunk(defeatsound, volume_unit* gSetting.power);
                            Mix_VolumeChunk(click_sound, volume_unit* gSetting.power / 3);
                        }
                        if (gMenu.highscore_btn->isTouch == true) {
                            Mix_PlayChannel(-1, click_sound, 0);
                            inHighScore = true;
                            while (inHighScore) {
                                curTime = SDL_GetTicks();
                                deltaTime = (float)(curTime - preTime) / 1000.f;
                                preTime = curTime;
                                gHighScore.Update(&event,game_font,screen);
                                SDL_RenderClear(screen);
                                gHighScore.RenderHighScore(screen);
                                SDL_RenderPresent(screen);
                                while (SDL_PollEvent(&event)) {
                                    if (event.type == SDL_QUIT) {
                                        inHighScore = false;
                                        inMenu = false;
                                        EndGame = false;
                                        PlayAgain = false;
                                    }
                                    gHighScore.Update(&event, game_font, screen);
                                    if (gHighScore.back_btn->isTouch == true) {
                                        inHighScore = false;
                                    }
                                }
                            }
                        }
                        if (gMenu.exit_btn->isTouch == true) { inMenu = false; PlayAgain = false; EndGame = false; Mix_PlayChannel(-1, click_sound, 0);
                        }
                    }

                }
            }
            updateHighScore("SourceGame//GameManager//record.txt", (int)score_val, std::to_string(getHighScore("SourceGame//GameManager//record.txt")));
        }
    }
    close(window, screen);
    return 0;
}



