#include "Laser.h"
#include "raymath.h"

Laser::Laser()//default constructor
{
	rayhit = {0};
	StartPos = {0.0f, 0.0f};
	Dir = Vector2Normalize({ 0.0f, 0.0f });
	thick = 0.0f;
	color = WHITE;
	next = NULL;
	prev = NULL;

}

Laser::Laser(Vector2 Start, Vector2 direction, RayCollision rayhits, float thickness, Color colors)//parameterized constructor
{
	this->StartPos = Start;
	this->Dir = direction;
	this->rayhit = rayhits;
	this->thick = thickness;
	this->color = colors;
	this->next = NULL;
	this->prev = NULL;
}

void Laser::Draw()
{
	Vector2 laser_startpos = StartPos;
	Vector2 laser_endpos = Dir;
	Color laser_color = color;
	float laser_thickness = thick;

	DrawLineEx(this->StartPos, {this->StartPos.x + this->Dir.x * 10.0f, this->StartPos.y + this->Dir.y * 10.0f }, this->thick, this->color);
}


void Laser::SetStartPos(Vector2 start)
{
	StartPos = start;
}

void Laser::SetDir(Vector2 direction)
{
	Dir = direction;
}

Vector2 Laser::GetStartPos()
{
	return StartPos;
}

Vector2 Laser::GetDir()
{
	return Dir;
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


