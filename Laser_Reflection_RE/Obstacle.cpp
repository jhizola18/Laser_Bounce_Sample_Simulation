#include "Obstacle.h"

Obstacle::Obstacle()
{
	Obstacle_id = 0;
	Obstacle_P1 = { 0 };
	Obstacle_P2 = { 0 };
	Obstacle_thick = 1.0f;
	Obstacle_color = WHITE;


}

Obstacle::Obstacle(uint32_t id, Vector2 p1, Vector2 p2)
{
	this->Obstacle_id = id;
	this->Obstacle_P1 = p1;
	this->Obstacle_P2 = p2;
	this->Obstacle_thick = 1.0f;
	this->Obstacle_color = WHITE;
}

void Obstacle::Draw()
{
	DrawLineEx(this->Obstacle_P1, this->Obstacle_P2, this->Obstacle_thick, this->Obstacle_color);
}
