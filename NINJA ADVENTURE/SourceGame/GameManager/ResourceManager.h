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
#define COOLDOWN_SKILL 2
#define BOSS1SPAWNTIME 30
#define BOSS2SPAWNTIME 60
#define PROTECTTIME 5


const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 540;
const int SCREEN_BPP = 32;
const std::string GAME_TITLE = "Ninja Adventure";
const SDL_Color CYAN_COLOR = { 0, 255, 255 };
const SDL_Color BLUE_COLOR = { 0, 0, 255 };
const SDL_Color ORANGE_COLOR = { 255, 165, 0 };
const SDL_Color YELLOW_COLOR = { 255, 255, 0 };
const SDL_Color LIME_COLOR = { 0, 255, 0 };
const SDL_Color PURPLE_COLOR = { 128, 0, 128 };
const SDL_Color RED_COLOR = { 255, 0, 0 };
const SDL_Color WHITE_COLOR = { 255, 255, 255 };
const SDL_Color BLACK_COLOR = { 0, 0, 0 };
const SDL_Color GREEN_COLOR = { 0, 128, 0 };

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
	PROTECT
};




	
