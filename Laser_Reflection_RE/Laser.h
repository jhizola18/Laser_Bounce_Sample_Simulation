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

	void SetRay(Ray ray);
	Ray GetRay();

	void SetEndPos(Vector2 Endpos);
	Vector2 GetEndPos();

	void SetCollision(RayCollision rayhits);
	RayCollision GetCollision();

	void SetThick(float thick);
	float GetThick();

	void GetColor(Color color);
	Color GetColor();


public:

	Laser* next;
	Laser* prev;

};