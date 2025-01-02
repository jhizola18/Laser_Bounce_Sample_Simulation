#pragma once
#include "raylib.h"
#include <memory>


class Laser {

public:
	Laser();
	Laser(uint32_t id ,Vector2 Start, Vector2 direction, RayCollision rayhits,float thickness, Color colors);
	void Draw()const;
	void SetStartPos(Vector2 start);
	Vector2 GetStartPos()const;
	
	void SetDir(Vector2 direction);
	Vector2 GetDir()const;

	void SetCollision(RayCollision rayhits);
	RayCollision GetCollision()const;

	float GetThick()const;

	Color GetColor()const;


public:

	uint32_t id;
	uint32_t currhit_id;
	Vector2 StartPos;
	Vector2 Dir;
	RayCollision rayhit;
	float thick;
	Color color;


	Laser* next;
	Laser* prev;

};