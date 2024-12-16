#pragma once
#include "LaserManager.h"


class Collision {
private:
	LaserManager Lasermanager;
public:
	Collision();
	void DetectCollision(LaserManager& Lasermanager);

};