#include "ResourceManager.h"
std::map<std::string, std::string> m_mapTexture;

void InitResoucre() {
	m_mapTexture["layer9"] = "DataGame//Textures//layer9.png";
	m_mapTexture["layer8"] = "DataGame//Textures//layer8.png";
	m_mapTexture["layer7"] = "DataGame//Textures//layer7.png";
	m_mapTexture["layer6"] = "DataGame//Textures//layer6.png";
	m_mapTexture["layer5"] = "DataGame//Textures//layer5.png";
	m_mapTexture["layer4"] = "DataGame//Textures//layer4.png";
	m_mapTexture["layer3"] = "DataGame//Textures//layer3.png";
	m_mapTexture["layer2"] = "DataGame//Textures//layer2.png";
	m_mapTexture["layer1"] = "DataGame//Textures//layer1.png";
    m_mapTexture["Idle"] = "DataGame//Textures//Idle.png";
	m_mapTexture["Run"] = "DataGame//Textures//Run.png";
	m_mapTexture["Jump"] = "DataGame//Textures//Jump.png";
	m_mapTexture["Fall"] = "DataGame//Textures//Fall.png";
	m_mapTexture["Death"] = "DataGame//Textures//Death.png";
	m_mapTexture["Attack"] = "DataGame//Textures//Attack.png";
    m_mapTexture["RinoRun"] = "DataGame//Textures//RinoRun.png";
    m_mapTexture["RinoHit"] = "DataGame//Textures//RinoHit.png";
    m_mapTexture["BatFly"] = "DataGame//Textures//BatFly.png";
    m_mapTexture["BatHit"] = "DataGame//Textures//BatHit.png";
    m_mapTexture["GoblinRun"] = "DataGame//Textures//GoblinRun.png";
    m_mapTexture["SkeletonWalk"] = "DataGame//Textures//SkeletonWalk.png";
    m_mapTexture["GoblinDeath"] = "DataGame//Textures//GoblinDeath.png";
    m_mapTexture["SkeletonDeath"] = "DataGame//Textures//SkeletonDeath.png";
    m_mapTexture["EyesFly"] = "DataGame//Textures//EyesFly.png";
    m_mapTexture["EyesHit"] = "DataGame//Textures//EyesHit.png";
    m_mapTexture["PurpleFly"] = "DataGame//Textures//PurpleFly.png";
    m_mapTexture["PurpleHit"] = "DataGame//Textures//PurpleHit.png";
    m_mapTexture["BossBite"] = "DataGame//Textures//BossBite.png";
    m_mapTexture["BossJump"] = "DataGame//Textures//BossJump.png";
    m_mapTexture["BossSkill"] = "DataGame//Textures//BossSkill.png";
    m_mapTexture["Bullet"] = "DataGame//Textures//Bullet.png";
    m_mapTexture["BulletImpact"] = "DataGame//Textures//BulletImpact.png";
    m_mapTexture["FireBall"] = "DataGame//Textures//FireBall.png";
    m_mapTexture["FireBallImpact"] = "DataGame//Textures//FireBallImpact.png";
    m_mapTexture["WaterBall"] = "DataGame//Textures//WaterBall2.png";
    m_mapTexture["WaterBallImpact"] = "DataGame//Textures//WaterBallImpact.png";
    m_mapTexture["Wind"] = "DataGame//Textures//Wind.png";
    m_mapTexture["WindImpact"] = "DataGame//Textures//WindImpact.png";
    m_mapTexture["Thunder"] = "DataGame//Textures//Thunder.png";
    m_mapTexture["ThunderImpact"] = "DataGame//Textures//ThunderImpact.png";
    m_mapTexture["WaterTornadoImpact"] = "DataGame//Textures//WaterTornadoImpact.png";
    m_mapTexture["WaterTornado"] = "DataGame//Textures//WaterTornado.png";
    m_mapTexture["SkillAvailable"] = "DataGame//Textures//SkillAvailable.png";
    m_mapTexture["SkillCooldown"] = "DataGame//Textures//SkillCooldown.png";
    m_mapTexture["Health0"] = "DataGame//Textures//Health0.png";
    m_mapTexture["Health1"] = "DataGame//Textures//Health1.png";
    m_mapTexture["Health2"] = "DataGame//Textures//Health2.png";
    m_mapTexture["Health3"] = "DataGame//Textures//Health3.png";
    m_mapTexture["Health4"] = "DataGame//Textures//Health4.png";
    m_mapTexture["Health5"] = "DataGame//Textures//Health5.png";
    m_mapTexture["Health6"] = "DataGame//Textures//Health6.png";
    m_mapTexture["EnergyCircle"] = "DataGame//Textures//EnergyCircle.png";
    m_mapTexture["bossnhen1"] = "DataGame//Textures//bossnhen1.png";
    m_mapTexture["bossnhen2"] = "DataGame//Textures//bossnhen2.png";
    m_mapTexture["Boss2Skill"] = "DataGame//Textures//Boss2Skill.png";
    m_mapTexture["Boss2SkillImpact"] = "DataGame//Textures//Boss2SkillImpact.png";
    m_mapTexture["Play"] = "DataGame//Textures//Play-sheet.png";
    m_mapTexture["Info"] = "DataGame//Textures//Info-sheet.png";
    m_mapTexture["Setting"] = "DataGame//Textures//Setting-sheet.png";
    m_mapTexture["HighScore"] = "DataGame//Textures//HighScore-sheet.png";
    m_mapTexture["Exit"] = "DataGame//Textures//Exit-sheet.png";
    m_mapTexture["Back"] = "DataGame//Textures//Back-sheet.png";
    m_mapTexture["Home"] = "DataGame//Textures//Home-sheet.png";
    m_mapTexture["Again"] = "DataGame//Textures//Again-sheet.png";
    m_mapTexture["Bkgrend"] = "DataGame//Textures//bkgrend.png";
    m_mapTexture["gametitle"] = "DataGame//Textures//game_title.png";
    m_mapTexture["Bkgrmenu"] = "DataGame//Textures//background.png";
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
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        std::cout << "Init audio failed. Error: " << SDL_GetError() << std::endl;
        success = 0;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cout << "Init audio failed. Error: " << SDL_GetError() << std::endl;
        success = 0;
    }
    if (TTF_Init() == -1)
    {
        std::cout << "Init font failed. Error: " << SDL_GetError() << std::endl;
        success = 0;
    }
    srand(time(0));
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

        //xet A
        if (leftA > leftB && leftA < rightB && topA > topB && topA < botB)
        {
                return true;
        }

        if (leftA > leftB && leftA < rightB && botA > topB && botA < botB)
        {
                return true;
        }

        if (rightA > leftB && rightA < rightB&& topA > topB && topA < botB)
        {
                return true;
        }

        if (rightA > leftB && rightA < rightB && botA > topB && botA < botB)
        {
                return true;
        }

        //xet B
        if (leftB > leftA && leftB < rightA && topB > topA && topB < botA)
        {
                return true;
        }

        if (leftB > leftA && leftB < rightA && botB > topA && botB < botA)
        {
                return true;
        }

        if (rightB > leftA && rightB < rightA&& topB > topA && topB < botA)
        {
                return true;

        }

        if (rightB > leftA && rightB < rightA&& botB > topA && botB < botA)
        {
                return true;         
        }

        //size A = size B
        if (topA == topB && rightA == rightB && botA == botB &&leftA==leftB)
        {
            return true;
        }

        return false;
}



