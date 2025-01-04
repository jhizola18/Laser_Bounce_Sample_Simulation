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

	Laser* addLaser(Vector2 Start, Vector2 End, RayCollision rayhits, float thickness, Color colors);
	void deleteLaser(Laser* &Anchor);
	void DeleteInChange(uint32_t& currId, uint32_t prevId, Laser*& Anchor);
	void Draw();
	void AnchorMovement();
	void InitLaserManager();
	uint32_t objectCount;
	uint32_t objectDrawn;
	Laser* const& GetAnchor_Laser() const;
	void SetAnchor_Laser(Laser* Anchor);

};