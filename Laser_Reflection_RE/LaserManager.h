#pragma once
#include "Laser.h"
#include <memory>

class LaserManager {
private:
	Laser* Anchor_Laser;
public:
	LaserManager();
	~LaserManager();

	Laser* addLaser(Vector2 Start, Vector2 End, RayCollision rayhits, float thickness, Color colors);
	void Draw();

	Laser* GetAnchor_Laser();

};