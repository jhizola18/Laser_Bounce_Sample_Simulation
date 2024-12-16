#pragma once
#include "LaserManager.h"
#include "Collision.h"
#include "raymath.h"


class Simulation {
private:
	LaserManager laser_manager;
public:
	Simulation();
	void MainSimulation();
	void DrawSimulation();
	void MovementSimulation();
};