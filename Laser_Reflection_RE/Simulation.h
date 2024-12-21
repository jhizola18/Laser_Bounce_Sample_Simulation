#pragma once
#include <iostream>
#include "LaserManager.h"
#include "Collision.h"
#include "raymath.h"
#include "Obstacle.h"
#include "Vector"


class Simulation {
private:
	LaserManager laser_manager;
	Obstacle obstacle;
	Collision collisionChecker;

public://functions and methods
	Simulation();
	void MainSimulation();
	void DrawSimulation();
	void MovementSimulation();

	std::vector<Obstacle> ShapeCreation();

public://containters and variables
	bool onHit;
	std::vector<Obstacle> ObstaclesStorage;
	uint32_t prevhit_id;
	uint32_t currhit_id;
	
};