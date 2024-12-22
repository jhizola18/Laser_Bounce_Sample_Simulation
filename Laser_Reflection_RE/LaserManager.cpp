
#include "LaserManager.h"


LaserManager::LaserManager()
	:
	LaserInit()
{
	Anchor_Laser = NULL;
	objectCount = 0;
	InitLaserManager();
}

LaserManager::~LaserManager() 
{
}

Laser* LaserManager::addLaser(uint64_t id,  Vector2 Start, Vector2 End, RayCollision rayhits, float thickness, Color colors)
{
	Laser* laser_temptr =  new Laser();
	if (Anchor_Laser == NULL) {
	
		Anchor_Laser = laser_temptr;
		
		laser_temptr->id = id;
		laser_temptr->StartPos = Start;
		laser_temptr->Dir = End;
		laser_temptr->rayhit.hit = rayhits.hit;
		laser_temptr->thick = thickness;
		laser_temptr->color = colors;
		objectCount++;
		return Anchor_Laser;
		
		
		
	}else {
		
		Laser* temptr = Anchor_Laser;
		while (temptr->next != NULL) {
			
			temptr = temptr->next;
		}

		objectCount++;
	
		temptr->next = laser_temptr;
		laser_temptr->prev = temptr;

		laser_temptr->id = id;
		laser_temptr->StartPos = Start;
		laser_temptr->Dir = End;
		laser_temptr->rayhit.hit = rayhits.hit;
		laser_temptr->thick = thickness;
		laser_temptr->color = colors;

	}
	return Anchor_Laser;
}

Laser* LaserManager::deleteLaser()
{
	Laser* temptr = Anchor_Laser;
	while (temptr != NULL) {
		
		temptr = temptr->next;
	}



	return Anchor_Laser;
}

void LaserManager::Draw()
{
	Laser* temptr = Anchor_Laser;
	std::cout << "\nNodes Created->" << objectCount << "\n";
	do {
		if (temptr == NULL) {
			break;
		}
		temptr->Draw();
		temptr = temptr->next;
	} while (temptr != NULL);

	
		
	
}

void LaserManager::AnchorMovement()
{
	if (IsCursorOnScreen()) {

		float AnchorNewX = GetMousePosition().x - Anchor_Laser->StartPos.x;
		float AnchorNewY = GetMousePosition().y - Anchor_Laser->StartPos.y;

		Vector2 NewAnchorPos = Vector2Normalize({AnchorNewX, AnchorNewY});
		Anchor_Laser->Dir.x = NewAnchorPos.x;
		Anchor_Laser->Dir.y = NewAnchorPos.y;
	}
}

void LaserManager::InitLaserManager()
{
	uint32_t id = 0;
	Vector2 start = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
	Vector2 end = Vector2Normalize({ 1.0f, 0.0f });
	float thick = 1.0f;
	Color color = RED;
	RayCollision rayhits = { 0 };
	rayhits.hit = false;
	Anchor_Laser =  addLaser(id, start, end, rayhits, thick, color);
}

Laser* LaserManager::GetAnchor_Laser()
{
	return Anchor_Laser;
}

void LaserManager::SetAnchor_Laser(Laser* Anchor)
{
	Anchor_Laser = Anchor;
}
