#include "CollisionManager.h"

void Collision::addObj(HitBox*a)
{
	listObj.push_back(a);
}

bool Collision::check(HitBox*a, HitBox* b)
{
	return checkCollision(a->box, b->box);
}

void Collision::Update()
{
	for (auto a : listObj) {
		if (a->isAlive == false) continue;
		for (auto b : listObj) {
			if (b->isAlive == false) continue;

			if (a->tag == b->tag) continue;
			if (!check(a, b)) continue;
			if (a->tag == PLAYER && b->tag == CREEP) {
				a->isAlive = false;
				b->isAlive = false;
				a->lives -= 1;
			}
			if (a->tag == PLAYER && b->tag == BOSS) {
				if (a->haveProtect == true) continue;
				a->isAlive = false;
				a->lives -= 2;
				if (a->lives < 0) a->lives = 0;
			}
			if (a->tag == PLAYER && b->tag == BOSS_BULLET) {
				a->isAlive = false;
				b->isAlive = false;
				a->lives -= 2;
				if (a->lives < 0) a->lives = 0;
			}
			if (a->tag == PLAYERSKILL && (b->tag == CREEP || b->tag == BOSS_BULLET))
			{
				a->isAlive = false;
				b->isAlive = false;
			}
			if (a->tag == PROTECT && (b->tag == CREEP || b->tag == BOSS_BULLET)) {
				b->isAlive = false;
			}
		}
	}
}
