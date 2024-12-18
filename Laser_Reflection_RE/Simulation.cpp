#include "Simulation.h"

Simulation::Simulation()
	:
	laser_manager()
{
	MainSimulation();
}

void Simulation::MainSimulation() 
{
	
		Vector2 start = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
		Vector2 end = Vector2Normalize({ 1.0f, 0.0f });
		float thick = 1.0f;
		Color color = RED;
		RayCollision rayhits = { 0 };
		rayhits.hit = false;
		laser_manager.addLaser(start,  end, rayhits, thick, color);
}


void Simulation::DrawSimulation()
{
	laser_manager.Draw();
}

void Simulation::MovementSimulation()
{
	laser_manager.AnchorMovement();
}
