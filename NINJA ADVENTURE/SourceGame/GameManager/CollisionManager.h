#pragma once
#include "ResourceManager.h"
class Collision
{
public:
	void addObj(HitBox* a);
	bool check(HitBox*a, HitBox* b);
	void Update();
private:
	std::vector<HitBox*> listObj;
};