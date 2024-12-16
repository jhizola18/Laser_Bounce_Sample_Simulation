#include "Simulation.h"

Simulation::Simulation()
	:
	laser_manager()
{

}

void Simulation::MainSimulation() 
{
	Vector2 start = {GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
	float endposx = start.x + 20.0f * 1000.0f;
	float endposy = start.y + 20.0f * 1000.0f;
	Vector2 end = {GetMouseX(), GetMouseY()};
	Vector2 endNorm = Vector2Normalize(end);
	float thick = 1.0f;
	Color color = RED;
	RayCollision rayhits = {0};
	rayhits.hit = false;
	laser_manager.addLaser(start, end, rayhits, thick, color);
}


void Simulation::DrawSimulation()
{
	laser_manager.Draw();
}

void Simulation::MovementSimulation()
{
	laser_manager.AnchorMovement();
}
