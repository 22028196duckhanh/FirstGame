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
			}
		}
	}
}
