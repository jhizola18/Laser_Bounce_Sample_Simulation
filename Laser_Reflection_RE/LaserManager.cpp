
#include "LaserManager.h"


LaserManager::LaserManager()
	:
	LaserInit()
{
	Anchor_Laser = nullptr;
	
	objectCount = 0;
	objectDrawn = 0;
	InitLaserManager();
}

LaserManager::~LaserManager() 
{
	Laser* store;
	Laser* temptr = Anchor_Laser;
	
	while (temptr != nullptr) {
		store = temptr->next;
		delete temptr; 
		std::cout << " Node Deleted ";
		temptr = store;
	}
	Anchor_Laser = nullptr;
	
}

Laser* LaserManager::addLaser(Vector2 Start, Vector2 End, RayCollision rayhits, float thickness, Color colors)
{
	Laser* laser_temptr =  new Laser();
	if (Anchor_Laser == nullptr) {

		Anchor_Laser = laser_temptr;
		laser_temptr->prev = nullptr;
		laser_temptr->id = objectCount  + 1;
		laser_temptr->StartPos = Start;
		laser_temptr->Dir = End;
		laser_temptr->rayhit.hit = rayhits.hit;
		laser_temptr->thick = thickness;
		laser_temptr->color = colors;
		objectCount++;
	
	}else {
		
		Laser* temptr = Anchor_Laser;
		while (temptr->next != nullptr) {
			
			temptr = temptr->next;
		}
		objectCount++;
		temptr->next = laser_temptr;
		laser_temptr->prev = temptr;
		laser_temptr->StartPos = Start;
		if (objectCount > 1) {
			laser_temptr->id = objectCount;
		}
		laser_temptr->Dir = End;
		laser_temptr->rayhit.hit = rayhits.hit;
		laser_temptr->thick = thickness;
		laser_temptr->color = colors;
		
	}
	return Anchor_Laser;
}

void LaserManager::deleteLaser(Laser* &Anchor)
{
	Laser *store, *temp;
	temp = Anchor;
	//DELETING NODE WHEN THE ANCHOR NODE COLLIDING TO NOTHING
	if (temp != nullptr && !Anchor_Laser->rayhit.hit) {
		//std::cout << "deleting process worked\n";
		//so the problem with the previous solution was its updating an already deleted pointer and possibly accessing it resulting to undefined behaviour 
		while (temp->next != nullptr) {
			//std::cout << " Object deleted: ID-> " << temp->next->id << "\n";
			store = temp->next;
			temp->next = store->next;
			if (store->next != nullptr) {
				store->next->prev = temp;
			}
			//std::cout << "Deleted ID: " << store->id << "\n";
			delete store;
			//std::cout << "\nDeleted all Tail\n";
			objectCount--;
		}
	}
	else {
		return;
	}
}

void LaserManager::DeleteInChange(uint32_t& currId, uint32_t prevId, Laser* &Anchor)
{
	if (currId != prevId && Anchor != nullptr) {
		deleteLaser(Anchor);
	}else {
		return;
	}
}

void LaserManager::Draw()
{
	Laser* temptr = Anchor_Laser;
	Anchor_Laser->Draw();
	while (temptr->next != nullptr) {

		if (temptr->rayhit.hit == true)
		{
				temptr->next->Draw();
				Vector2 PoI = { temptr->rayhit.point.x, temptr->rayhit.point.y };
				DrawCircleV(PoI, 3.0f, GREEN);
		}
		else {
			break;
		}
		
		temptr = temptr->next;
	}
		
	
}

void LaserManager::AnchorMovement()
{

	if (IsCursorOnScreen()) {

		float AnchorNewX = GetMousePosition().x - Anchor_Laser->StartPos.x;
		float AnchorNewY = GetMousePosition().y - Anchor_Laser->StartPos.y;

		Vector2 NewAnchorPos = Vector2Normalize({ AnchorNewX, AnchorNewY });
		Anchor_Laser->Dir.x = NewAnchorPos.x;
		Anchor_Laser->Dir.y = NewAnchorPos.y;
	}

}



void LaserManager::InitLaserManager()
{
	Vector2 start = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
	Vector2 end = Vector2Normalize({ 1.0f, 0.0f });
	Color color = RED;
	RayCollision rayhits = { 0 };
	float thick = 1.0f;
	rayhits.hit = false;
	Anchor_Laser = addLaser(start ,end, rayhits, thick, color);
}



Laser* LaserManager::GetAnchor_Laser() const
{
	return Anchor_Laser;
}

void LaserManager::SetAnchor_Laser(Laser* Anchor)
{
	Anchor_Laser = Anchor;
}
