#include "Laser.h"
#include "raymath.h"

Laser::Laser()//default constructor
{
	id = 0;
	currhit_id = 0;
	rayhit = {0};
	StartPos = {0.0f, 0.0f};
	Dir = Vector2Normalize({ 0.0f, 0.0f });
	change_of_obj_collision = false;
	thick = 0.0f;
	color = RED;
	next = NULL;
	prev = NULL;

}

Laser::Laser(uint32_t id, Vector2 Start, Vector2 direction, RayCollision rayhits, float thickness, Color colors)//parameterized constructor
{
	this->currhit_id = 0;
	this->id = id;
	this->StartPos = Start;
	this->Dir = direction;
	this->rayhit = rayhits;
	this->change_of_obj_collision = false;
	this->thick = thickness;
	this->color = colors;
	this->next = NULL;
	this->prev = NULL;
}

void Laser::Draw() const
{
	if (this->rayhit.hit == false) {
		DrawLineEx(this->StartPos, { this->StartPos.x + this->Dir.x * 1000.0f, this->StartPos.y + this->Dir.y * 1000.0f }, this->thick, this->color);
	}
	else{
		DrawLineEx(this->StartPos, { this->rayhit.point.x, this->rayhit.point.y}, this->thick, this->color);
	}
}


void Laser::SetStartPos(Vector2 start)
{
	StartPos = start;
}

void Laser::SetDir(Vector2 direction)
{
	Dir = direction;
}

Vector2 Laser::GetStartPos() const
{
	return StartPos;
}

Vector2 Laser::GetDir() const
{
	return Dir;
}

void Laser::SetCollision(RayCollision rayhits)
{
	rayhit = rayhits;
}

RayCollision Laser::GetCollision() const
{

	return rayhit;
}

float Laser::GetThick() const
{
	return thick;
}

Color Laser::GetColor() const
{
	return color;
}


