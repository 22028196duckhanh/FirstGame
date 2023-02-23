#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <ctime>
#include "../GameObject/Animation.h"
#include "../GameObject/HitBox.h"

#define FPS 45
#define GROUND_Y 495
#define GRAVITY 50
#define MAX_HEIGHT 350
#define COOLDOWN_SKILL 5

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 540;
const int SCREEN_BPP = 32;
const std::string GAME_TITLE = "Ninja Adventure";

extern std::map<std::string, std::string> m_mapTexture;
extern std::map<std::string, std::string> m_mapSound;

void InitResoucre();
bool initWorld(SDL_Window*& window, SDL_Renderer*& screen);
void close(SDL_Window*& window, SDL_Renderer*& screen);

bool checkCollision(const SDL_Rect& object1, const SDL_Rect& object2);

typedef struct {
	float x;
	float y;
} Vector2d;

enum TAG {
	PLAYER = 0,
	PLAYERSKILL,
	CREEP,
	BOSS,
	BOSS_BULLET,
};




	
