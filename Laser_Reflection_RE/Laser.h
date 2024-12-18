#pragma once
#include "raylib.h"
#include <memory>

class Laser {

public:
	Laser();
	Laser(Vector2 Start, Vector2 direction, RayCollision rayhits,float thickness, Color colors);
	void Draw();
	void SetStartPos(Vector2 start);
	Vector2 GetStartPos();
	
	void SetDir(Vector2 direction);
	Vector2 GetDir();

	void SetCollision(RayCollision rayhits);
	RayCollision GetCollision();

	float GetThick();

	Color GetColor();


public:

	Vector2 StartPos;
	Vector2 Dir;
	RayCollision rayhit;
	float thick;
	Color color;


	Laser* next;
	Laser* prev;

};