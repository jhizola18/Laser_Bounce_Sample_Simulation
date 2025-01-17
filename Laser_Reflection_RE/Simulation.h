#pragma once
#include <iostream>
#include "LaserManager.h"
#include "Collision.h"
#include "raymath.h"
#include "Obstacle.h"
#include "Vector"
#include "limits"

#define MAX_BOUNCE 11

class Simulation {
private:
	LaserManager laser_manager;
	Laser* temp_Anchor;
	Obstacle obstacle;
	Collision collisionChecker;

public://functions and methods
	Simulation();
	~Simulation()noexcept;
	void MainSimulation();
	void DrawSimulation();
	void DetectChangeCollision();
	void MovementSimulation();
	void UpdateSimulation();

	std::vector<Obstacle> ShapeCreation();
	std::vector<uint32_t> prev_Values;

public://containters and variables
	bool onHit;
	std::vector<Obstacle> ObstaclesStorage;
	uint32_t prevhit_id;
	uint32_t currhit_id;
	
};