#include <iostream>
#include "LaserManager.h"


LaserManager::LaserManager()
	:
	LaserInit()
{
	Anchor_Laser = NULL;
	objectCount = 0;
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
		objectCount++;
		
	}else {
		
		Laser* temptr = Anchor_Laser;
		while (temptr->next != NULL) {
			
			temptr = temptr->next;
		}
		float prevthick = temptr->GetThick();
		RayCollision rayhits = {0};
		Vector2 prevStartpos = { temptr->GetCollision().point.x,  temptr->GetCollision().point.y };
		Vector2 prevEndpos = {500.0f, 500.0f};
		rayhits.hit = false;
		Color prevColor = temptr->GetColor();

		Laser* laser_temptr = new Laser(prevStartpos, prevEndpos, rayhits, prevthick, prevColor);
		objectCount++;
		temptr->next = laser_temptr;
		laser_temptr->prev = temptr;
		
		
	}
	
	
	return Anchor_Laser;
}

void LaserManager::Draw()
{
	Laser* temptr = Anchor_Laser;
	std::cout << objectCount << " ";
	while (temptr != NULL) {

		temptr->Draw();
		temptr = temptr->next;
		
	}
}

void LaserManager::AnchorMovement()
{
	//This is causing the bug
	//Why its not moving correctly???am i looking at the right problem??????maybe it has something to do with constructor?????,maybe consider the dir
	if (IsCursorOnScreen()) {
		
		std::cout << "Anchor Old X: " << Anchor_Laser->StartPos.x << "\n";
		std::cout << "\nAnchor Old Y: " << Anchor_Laser->StartPos.y << "\n";

		float AnchorNewX = GetMousePosition().x - Anchor_Laser->StartPos.x;
		float AnchorNewY = GetMousePosition().y - Anchor_Laser->StartPos.y;

		std::cout << "Anchor New X: " << AnchorNewX << "\n";
		std::cout << "\nAnchor New Y: " << AnchorNewY << "\n";
		std::cout << "\nOriginal Dir X: " << Anchor_Laser->Dir.x << "\n";
		std::cout << "\nOriginal Dir Y: " << Anchor_Laser->Dir.y << "\n";

		Vector2 NewAnchorPos = Vector2Normalize({AnchorNewX, AnchorNewY});
		Anchor_Laser->Dir.x = NewAnchorPos.x;
		Anchor_Laser->Dir.y = NewAnchorPos.y;
		Vector2Normalize(Anchor_Laser->Dir);

		std::cout << "\nNew Dir X: " << Anchor_Laser->Dir.x << "\n";
		std::cout << "\nNew Dir Y: " << Anchor_Laser->Dir.y << "\n";
		
		
	}
}

Laser* LaserManager::GetAnchor_Laser()
{
	return Anchor_Laser;
}
