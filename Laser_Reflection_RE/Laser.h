#pragma once
#include "raylib.h"
#include <memory>

class Laser {
private:
	Vector2 StartPos;
	Vector2 EndPos;
	RayCollision rayhit;
	float thick;
	Color color;

	

public:
	Laser();
	Laser(Vector2 Start, Vector2 End, RayCollision rayhits,float thickness, Color colors);
	void Draw();

	void SetStartPos(Vector2 start);
	Vector2 GetStartPos();
	
	void SetEndPos(Vector2 end);
	Vector2 GetEndPos();

	void SetCollision(RayCollision rayhits);
	RayCollision GetCollision();

	float GetThick();

	Color GetColor();


public:

	Laser* next;
	Laser* prev;

};