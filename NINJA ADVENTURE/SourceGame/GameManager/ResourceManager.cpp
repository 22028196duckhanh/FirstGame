#include "ResourceManager.h"
std::map<std::string, std::string> m_mapTexture;
std::map<std::string, std::string> m_mapSound;

void InitResoucre() {
	m_mapTexture["layer9"] = "C://GAME_PROJECT//NINJA ADVENTURE//DataGame//Textures//layer9.png";
	m_mapTexture["layer8"] = "C://GAME_PROJECT//NINJA ADVENTURE//DataGame//Textures//layer8.png";
	m_mapTexture["layer7"] = "C://GAME_PROJECT//NINJA ADVENTURE//DataGame//Textures//layer7.png";
	m_mapTexture["layer6"] = "C://GAME_PROJECT//NINJA ADVENTURE//DataGame//Textures//layer6.png";
	m_mapTexture["layer5"] = "C://GAME_PROJECT//NINJA ADVENTURE//DataGame//Textures//layer5.png";
	m_mapTexture["layer4"] = "C://GAME_PROJECT//NINJA ADVENTURE//DataGame//Textures//layer4.png";
	m_mapTexture["layer3"] = "C://GAME_PROJECT//NINJA ADVENTURE//DataGame//Textures//layer3.png";
	m_mapTexture["layer2"] = "C://GAME_PROJECT//NINJA ADVENTURE//DataGame//Textures//layer2.png";
	m_mapTexture["layer1"] = "C://GAME_PROJECT//NINJA ADVENTURE//DataGame//Textures//layer1.png";
	m_mapTexture["Run"] = "C://GAME_PROJECT//NINJA ADVENTURE//DataGame//Textures//Run.png";
	m_mapTexture["Jump"] = "C://GAME_PROJECT//NINJA ADVENTURE//DataGame//Textures//Jump.png";
	m_mapTexture["Fall"] = "C://GAME_PROJECT//NINJA ADVENTURE//DataGame//Textures//Fall.png";
	m_mapTexture["Death"] = "C://GAME_PROJECT//NINJA ADVENTURE//DataGame//Textures//Death.png";
	m_mapTexture["Attack"] = "C://GAME_PROJECT//NINJA ADVENTURE//DataGame//Textures//Attack.png";
    m_mapTexture["RinoRun"] = "C://GAME_PROJECT//NINJA ADVENTURE//DataGame//Textures//RinoRun.png";
    m_mapTexture["RinoHit"] = "C://GAME_PROJECT//NINJA ADVENTURE//DataGame//Textures//RinoHit.png";
    m_mapTexture["BatFly"] = "C://GAME_PROJECT//NINJA ADVENTURE//DataGame//Textures//BatFly.png";
    m_mapTexture["BatHit"] = "C://GAME_PROJECT//NINJA ADVENTURE//DataGame//Textures//BatHit.png";
    m_mapTexture["GoblinRun"] = "C://GAME_PROJECT//NINJA ADVENTURE//DataGame//Textures//GoblinRun.png";
    m_mapTexture["SkeletonWalk"] = "C://GAME_PROJECT//NINJA ADVENTURE//DataGame//Textures//SkeletonWalk.png";
    m_mapTexture["GoblinDeath"] = "C://GAME_PROJECT//NINJA ADVENTURE//DataGame//Textures//GoblinDeath.png";
    m_mapTexture["SkeletonDeath"] = "C://GAME_PROJECT//NINJA ADVENTURE//DataGame//Textures//SkeletonDeath.png";
}
bool initWorld(SDL_Window*& window, SDL_Renderer*& screen) {
    bool success = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "Init failed. Error: " << SDL_GetError() << std::endl;
        success = 0;
    }
    window = SDL_CreateWindow(GAME_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        std::cout << "Create window failed. Error: " << SDL_GetError() << std::endl;
        success = 0;
    }
    screen = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (screen == NULL) {
        std::cout << "Create renderer failed. Error: " << SDL_GetError() << std::endl;
        success = 0;
    }
    if (!IMG_Init(IMG_INIT_PNG)) {
        std::cout << "Init image failed. Error: " << SDL_GetError() << std::endl;
        success = 0;
    }
    return success;
}
void close(SDL_Window*& window, SDL_Renderer*& screen) {
    SDL_DestroyRenderer(screen);
    screen = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

bool checkCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{       
    int leftA = object1.x;
    int rightA = object1.x + object1.w;
    int topA = object1.y;
    int botA = object1.y + object1.h;

    int leftB = object2.x;
    int rightB = object2.x + object2.w;
    int topB = object2.y;
    int botB = object2.y + object2.h;

        // Case 1: size object 1 < size object 2
        if (leftA > leftB && leftA < rightB)
        {
            if (topA > topB && topA < botB)
            {
                return true;
            }
        }

        if (leftA > leftB && leftA < rightB)
        {
            if (botA > topB && botA < botB)
            {
                return true;
            }
        }

        if (rightA > leftB && rightA < rightB)
        {
            if (topA > topB && topA < botB)
            {
                return true;
            }
        }

        if (rightA > leftB && rightA < rightB)
        {
            if (botA > topB && botA < botB)
            {
                return true;
            }
        }

        // Case 2: size object 1 < size object 2
        if (leftB > leftA && leftB < rightA)
        {
            if (topB > topA && topB < botA)
            {
                return true;
            }
        }

        if (leftB > leftA && leftB < rightA)
        {
            if (botB > topA && botB < botA)
            {
                return true;
            }
        }

        if (rightB > leftA && rightB < rightA)
        {
            if (topB > topA && topB < botA)
            {
                return true;
            }
        }

        if (rightB > leftA && rightB < rightA)
        {
            if (botB > topA && botB < botA)
            {
                return true;
            }
        }

        // Case 3: size object 1 = size object 2
        if (topA == topB && rightA == rightB && botA == botB)
        {
            return true;
        }

        return false;
}



