#pragma once
#include <iostream>
#include "raylib.h"


class Obstacle {
public:
	Obstacle();
	Obstacle(uint32_t id,Vector2 p1, Vector2 p2);
	void Draw();

public:

	uint32_t Obstacle_id;
	Vector2 Obstacle_P1;
	Vector2 Obstacle_P2;
	float Obstacle_thick;
	Color Obstacle_color;

};