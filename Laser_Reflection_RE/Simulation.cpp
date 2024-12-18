#include "Simulation.h"

Simulation::Simulation()
	:
	laser_manager()
{
	ObstaclesStorage = ShapeCreation();
}

void Simulation::MainSimulation() 
{
}


void Simulation::DrawSimulation()
{
	laser_manager.Draw();

	for (auto& items: ObstaclesStorage) {

		items.Draw();
	}
	
}

void Simulation::MovementSimulation()
{
	laser_manager.AnchorMovement();
}

//Hardcoded Obstacle
std::vector<Obstacle> Simulation::ShapeCreation()
{
	std::vector<Obstacle> temp_storage;
	//Plane 1
	Vector2 P1 = {300.0f, 300.0f};
	Vector2 P2 = {500.0f, 300.0f};
	Obstacle obstacle = Obstacle(P1, P2);

	temp_storage.push_back(obstacle);

	//Plane 1 Checker for clipping outside the collision
	Vector2 P1Checker = { 300.0f, 250.0f };
	Vector2 P2Checker = { 700.0f, 250.0f };
	Obstacle obstacleChecker = Obstacle(P1Checker, P2Checker);

	temp_storage.push_back(obstacleChecker);


	//Plane 2
	Vector2 P3 = {250.0f, 300.0f};
	Vector2 P4 = {250.0f, 400.0f};
	Obstacle obstacle1 = Obstacle(P3, P4);

	temp_storage.push_back(obstacle1);

	//Plane 2 Checker for clipping outside the collision
	Vector2 P3Checker = { 200.0f, 300.0f };
	Vector2 P4Checker = { 200.0f, 500.0f };
	Obstacle obstacle1Checker = Obstacle(P3Checker, P4Checker);

	temp_storage.push_back(obstacle1Checker);

	
	//Plane 3 
	Vector2 P5 = { 300.0f, 500.0f };
	Vector2 P6 = { 550.0f, 300.0f };
	Obstacle obstacle2 = Obstacle(P5, P6);

	temp_storage.push_back(obstacle2);

	//Plane 4
	Vector2 P7 = { 180.0f, 550.0f };
	Vector2 P8 = { 650.0f, 550.0f };
	Obstacle obstacle3 = Obstacle(P7, P8);

	temp_storage.push_back(obstacle3);


	return temp_storage;
}
