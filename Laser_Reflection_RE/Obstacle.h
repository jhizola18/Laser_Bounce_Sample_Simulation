#pragma once
#include "raylib.h"


class Obstacle {
public:
	Obstacle();
	Obstacle(Vector2 p1, Vector2 p2);
	void Draw();

public:

	Vector2 Obstacle_P1;
	Vector2 Obstacle_P2;
	float Obstacle_thick;
	Color Obstacle_color;

};