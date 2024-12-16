#include "Laser.h"

Laser::Laser()//default constructor
{
	rayhit = {0};
	StartPos = {0.0f, 0.0f};
	EndPos = {0.0f, 0.0f};
	thick = 0.0f;
	color = WHITE;
	next = NULL;
	prev = NULL;

}

Laser::Laser(Vector2 Start, Vector2 End, RayCollision rayhits, float thickness, Color colors)//parameterized constructor
{
	this->StartPos = Start;
	this->EndPos = End;
	this->rayhit = rayhits;
	this->thick = thickness;
	this->color = colors;
	this->next = NULL;
	this->prev = NULL;
}

void Laser::Draw()
{
	Vector2 laser_startpos = StartPos;
	Vector2 laser_endpos = EndPos;
	Color laser_color = color;
	float laser_thickness = thick;

	DrawLineEx(laser_startpos, laser_endpos, laser_thickness, laser_color);
}

void Laser::SetStartPos(Vector2 start)
{
	StartPos = start;
}

void Laser::SetEndPos(Vector2 end)
{
	EndPos = end;
}

Vector2 Laser::GetStartPos()
{
	return StartPos;
}

Vector2 Laser::GetEndPos()
{
	return EndPos;
}

void Laser::SetCollision(RayCollision rayhits)
{
	rayhit = rayhits;
}

RayCollision Laser::GetCollision() {

	return rayhit;
}

float Laser::GetThick() 
{
	return thick;
}

Color Laser::GetColor()
{
	return color;
}


