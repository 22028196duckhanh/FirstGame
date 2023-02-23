#include "SourceGame/GameManager/ResourceManager.h"
#include "SourceGame/GameManager/CollisionManager.h"
#include "SourceGame/GameObject/ParallaxBackground.h"
#include "SourceGame/GameObject/Player.h"
#include "SourceGame/GameObject/Creep.h"
#include "SourceGame/GameObject/CreepSpawn.h"

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* screen = NULL;
    SDL_Event event;


    initWorld(window, screen);
    InitResoucre();

    ParallaxBG bkground;
    Player player;
    Collision interactObj;
    CreepManager creepmanager;

    bkground.Init(screen);
    player.Init(screen);
    creepmanager.Init(interactObj, screen);

    interactObj.addObj(player.getHitBox());


    std::cout << "SKILL AVAILABLE" << std::endl;
    
    Uint32 curTime = 0;
    Uint32 preTime = 0;
    float deltaTime = 0.f;
    float cooldownTime = 0.f;
    bool is_quit = false;
    while (!is_quit) {

        curTime = SDL_GetTicks();
        deltaTime = (float)(curTime - preTime) / 1000.f;
        preTime = curTime;
        if (player.skillAvailable==false) cooldownTime += deltaTime;
        if (cooldownTime > COOLDOWN_SKILL) { 
            std::cout << "SKILL AVAILABLE" << std::endl; 
            player.skillAvailable = true;
            cooldownTime = 0;
        }

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                is_quit = true;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                is_quit = true;
            
        }
        player.InputAction();
        SDL_RenderClear(screen);
        SDL_SetRenderDrawColor(screen, 255, 255, 255, 255);

        if(player.getHitBox()->isAlive==true) bkground.Update();
        player.Update(deltaTime);
        creepmanager.Update(deltaTime);
        interactObj.Update();


        bkground.RenderBG(screen);
        player.renderPlayer(screen);
        creepmanager.renderManyCreep(screen);
        SDL_RenderPresent(screen);

        if (1000 / FPS > deltaTime)
            SDL_Delay((1000 / FPS) - deltaTime);
    }
    close(window, screen);
    return 0;
}

