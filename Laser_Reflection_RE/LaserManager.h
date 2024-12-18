#pragma once
#include "Laser.h"
#include <memory>
#include "raymath.h"

class LaserManager {
private:
	Laser* Anchor_Laser;
	Laser LaserInit;
public:
	LaserManager();
	~LaserManager();

	Laser* addLaser(Vector2 Start, Vector2 End, RayCollision rayhits, float thickness, Color colors);
	void Draw();
	void AnchorMovement();
	int objectCount;
	Laser* GetAnchor_Laser();

};