#include "LaserManager.h"

LaserManager::LaserManager()
{
	Anchor_Laser = NULL;
}

LaserManager::~LaserManager() 
{
	
}

Laser* LaserManager::addLaser(Vector2 Start, Vector2 End, RayCollision rayhits, float thickness, Color colors)
{
	

	if (Anchor_Laser == NULL) {

		Laser* laser_temptr = new Laser(Start, End, rayhits, thickness, colors);

		laser_temptr->next = Anchor_Laser;
		Anchor_Laser = laser_temptr;
		
	}
	else {
		
		Laser* temptr = Anchor_Laser;
		while (temptr != NULL) {
			
			temptr = temptr->next;
		}
		

		float prevthick = temptr->GetThick();
		RayCollision rayhits = {0};
		Vector2 prevStartpos = { rayhits.point.x, rayhits.point.y };
		Vector2 prevEndpos = {End.x, End.y};
		rayhits.hit = false;
		Color prevColor = temptr->GetColor();

		Laser* laser_temptr = new Laser(prevStartpos, prevEndpos, rayhits, prevthick, prevColor);

		temptr->next = laser_temptr;
		laser_temptr->prev = temptr;

		
	}

	return Anchor_Laser;
}

void LaserManager::Draw()
{
	
}

Laser* LaserManager::GetAnchor_Laser()
{
	return Anchor_Laser;
}
