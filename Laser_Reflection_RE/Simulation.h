#pragma once
#include "LaserManager.h"
#include "Collision.h"
#include "raymath.h"
#include "Obstacle.h"
#include "vector"


class Simulation {
private:
	LaserManager laser_manager;
	Obstacle obstacle;

public://functions and methods
	Simulation();
	void MainSimulation();
	void DrawSimulation();
	void MovementSimulation();

	std::vector<Obstacle> ShapeCreation();

public://containters and variables
	std::vector<Obstacle> ObstaclesStorage;
};