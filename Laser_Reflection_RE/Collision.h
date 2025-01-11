#pragma once
#include "LaserManager.h"
#include "Obstacle.h"

class Collision {
private:
	LaserManager Lasermanager;
	bool IntersectingLines(Obstacle& obs, Laser*& laser);
public:
	Collision();
	bool DetectCollision(Obstacle& obs, Laser* &laser);
	Vector2 PointOfIntersection(Vector2 P1, Vector2 P2, float t, float u);

public:

	float t;
	float u;

};