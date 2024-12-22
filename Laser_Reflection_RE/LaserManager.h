#pragma once
#include <iostream>
#include "Laser.h"
#include "raymath.h"

class LaserManager {
private:
	Laser* Anchor_Laser;
	Laser LaserInit;
public:
	LaserManager();
	~LaserManager();

	Laser* addLaser(uint64_t id ,Vector2 Start, Vector2 End, RayCollision rayhits, float thickness, Color colors);
	Laser* deleteLaser();
	void Draw();
	void AnchorMovement();
	void InitLaserManager();
	int objectCount;
	Laser* GetAnchor_Laser();
	void SetAnchor_Laser(Laser* Anchor);

};