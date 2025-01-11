#include "Simulation.h"

float runningTime = 1.0f / 5.0f;
float updateTime = 0.0f;

Simulation::Simulation()
	:
	laser_manager(),
	collisionChecker()
{
	temp_Anchor = laser_manager.GetAnchor_Laser();
	ObstaclesStorage = ShapeCreation();
	prev_Values = { 0 };
	prevhit_id = 0;
	currhit_id = 0;
	onHit = false;
}

Simulation::~Simulation() noexcept 
{
	temp_Anchor = nullptr;
	for (uint32_t obstacle = 0; obstacle < ObstaclesStorage.size(); ++obstacle) {
		ObstaclesStorage.pop_back();
	}
}
void Simulation::MainSimulation() 
{
	Laser* temptr = temp_Anchor;
	Vector2 Start = { 0 };
	Vector2 PoI = { 0 };
	Vector2 P1toP2 = { 0 };
	Vector2 Reflect = { 0 };
	RayCollision rayhits = { 0 };
	float thickness = 0.0f;
	Color color = WHITE;
	
	do {
		
		if (temptr == nullptr) {
			break;
		}
	
		for (size_t obstacle = 0; obstacle < ObstaclesStorage.size(); ++obstacle) {
			
			if (collisionChecker.DetectCollision(ObstaclesStorage[obstacle], temptr)) {
				thickness = 1.0f;
				color = RED;
				rayhits.hit = false;
				temptr->currhit_id = ObstaclesStorage[obstacle].Obstacle_id;
				
				temptr->rayhit.hit = true;
				temptr->rayhit.point.x = PoI.x;
				temptr->rayhit.point.y = PoI.y;
				P1toP2 = { ObstaclesStorage[obstacle].Obstacle_P2.x - ObstaclesStorage[obstacle].Obstacle_P1.x, ObstaclesStorage[obstacle].Obstacle_P2.y - ObstaclesStorage[obstacle].Obstacle_P1.y };
				Reflect = Vector2Reflect(Vector2Normalize(temptr->Dir), Vector2Normalize({ -P1toP2.y, P1toP2.x }));
				
				if (!ObstaclesStorage[obstacle].active) {
					
				
					if (laser_manager.objectCount >= 11) {
						break;
					}
					Vector2 start = { temptr->rayhit.point.x , temptr->rayhit.point.y };
					temp_Anchor = laser_manager.addLaser(start, Reflect, rayhits, thickness, color);
					ObstaclesStorage[obstacle].active = true;
				}
				else {
					
					ObstaclesStorage[obstacle].active = false;
				}
				
				break;
			}else {
				temptr->currhit_id = 0;
				temptr->rayhit.hit = false;
				
			}
		}
		if (temp_Anchor->rayhit.hit == false) {
			laser_manager.deleteLaser(temp_Anchor);
		}
		
		temptr = temptr->next;
	
	} while (temptr != nullptr);
	
	
}



void Simulation::DrawSimulation()
{
	laser_manager.Draw();
	for (auto& items: ObstaclesStorage) {

		items.Draw();
	}
	
}

void Simulation::DetectChangeCollision()
{
	if (temp_Anchor->currhit_id != prev_Values.back()) {
		prevhit_id = prev_Values.back();
	}
	else if(temp_Anchor->currhit_id == prev_Values.back()){
		
		temp_Anchor->currhit_id = temp_Anchor->currhit_id;
	}

	if (prev_Values.size() > 13) {
		prev_Values.erase(prev_Values.begin());
	}
	else {
		prev_Values.push_back(temp_Anchor->currhit_id);
	}

}


void Simulation::MovementSimulation()
{
	laser_manager.AnchorMovement();
	UpdateSimulation();
}

//solve this updating problem
void Simulation::UpdateSimulation()
{
	Laser* temp = temp_Anchor->next;
	Vector2 reflect = {0};
	Vector2 P1toP2 = {0};
	Vector2 PoI = {0};
	bool near = false;
	do {
		if (temp == nullptr) {
			break;
		}
	
				for (size_t obstacle = 0; obstacle < ObstaclesStorage.size(); ++obstacle) {
					float record = std::numeric_limits<float>::infinity();
					Vector2 closest = { 0 };
					near = false;
					if (collisionChecker.DetectCollision(ObstaclesStorage[obstacle], temp->prev)) {
						PoI = collisionChecker.PointOfIntersection(ObstaclesStorage[obstacle].Obstacle_P1, ObstaclesStorage[obstacle].Obstacle_P2, collisionChecker.t, collisionChecker.u);
						float distance = Vector2Distance(temp->StartPos, PoI);
						if (distance < record) {

							record = distance;
							closest = PoI;
							near = true;
						}
						else {
							false;
						}
						
						if (near) {
							temp->prev->rayhit.point.x = closest.x;
							temp->prev->rayhit.point.y = closest.y;
						}
						else {
							temp->prev->rayhit.point.x = PoI.x;
							temp->prev->rayhit.point.y = PoI.y;
						}
						

						P1toP2 = Vector2Subtract(ObstaclesStorage[obstacle].Obstacle_P2, ObstaclesStorage[obstacle].Obstacle_P1);
						reflect = Vector2Reflect(Vector2Normalize(temp->prev->Dir), Vector2Normalize({ -P1toP2.y, P1toP2.x }));
						temp->StartPos = { temp->prev->rayhit.point.x,temp->prev->rayhit.point.y };
						temp->Dir = reflect;
						break;
					}
					
				}
			
			temp = temp->next;
		} while (temp != nullptr);

		
	
		
	
}


//Hardcoded Obstacle
std::vector<Obstacle> Simulation::ShapeCreation()
{
	std::vector<Obstacle> temp_storage;
	//Plane 1
	Vector2 P1 = {300.0f, 300.0f};
	Vector2 P2 = {500.0f, 300.0f};
	uint32_t id1 = 1;
	Obstacle obstacle = Obstacle(id1,P1, P2);

	temp_storage.push_back(obstacle);

	//Plane 1 Checker for clipping outside the collision
	Vector2 P1Checker = { 300.0f, 250.0f };
	Vector2 P2Checker = { 700.0f, 250.0f };
	uint32_t id2 = 2;
	Obstacle obstacleChecker = Obstacle(id2,P1Checker, P2Checker);

	temp_storage.push_back(obstacleChecker);

	//Plane 2
	Vector2 P3 = {250.0f, 300.0f};
	Vector2 P4 = {250.0f, 400.0f};
	uint32_t id3 = 3;
	Obstacle obstacle1 = Obstacle(id3,P3, P4);

	temp_storage.push_back(obstacle1);

	//Plane 2 Checker for clipping outside the collision
	srand(time(0));

	float minRandX = rand() % 200;
	float minRandY = rand() % 200;
	float maxRandX = rand() % 700;
	float maxRandY = rand() % 700;
	
	Vector2 P3Checker = { minRandX, minRandY };
	Vector2 P4Checker = { maxRandX, maxRandY };
	uint32_t id4 = 4;
	Obstacle obstacle1Checker = Obstacle(id4,P3Checker, P4Checker);

	temp_storage.push_back(obstacle1Checker);

	
	//Plane 3 
	Vector2 P5 = { 300.0f, 500.0f };
	Vector2 P6 = { 550.0f, 300.0f };
	uint32_t id5 = 5;
	Obstacle obstacle2 = Obstacle(id5,P5, P6);

	temp_storage.push_back(obstacle2);

	//Plane 4
	Vector2 P7 = { 180.0f, 550.0f };
	Vector2 P8 = { 650.0f, 550.0f };
	uint32_t id6 = 6;
	Obstacle obstacle3 = Obstacle(id6,P7, P8);

	temp_storage.push_back(obstacle3);


	return temp_storage;
}



//DON'T DELETE THIS 
/*for (auto& items : ObstaclesStorage) {
			//Fix it so when the anchor laser moves the other parts moves too :HOW TO FUCKING DO THIS
			if (collisionChecker.DetectCollision(items, temptr)) {
				PoI = collisionChecker.PointOfIntersection(items.Obstacle_P1, items.Obstacle_P2, collisionChecker.t, collisionChecker.u);
				temptr->rayhit.hit = true;
				currhit_id = items.Obstacle_id;
				rayhits.point.x = PoI.x;
				rayhits.point.y = PoI.y;
				temptr->rayhit.point.x = PoI.x;
				temptr->rayhit.point.y = PoI.y;
				rayhits.hit = false;
				P1toP2 = { items.Obstacle_P2.x - items.Obstacle_P1.x, items.Obstacle_P2.y - items.Obstacle_P1.y };
				Reflect = Vector2Reflect(Vector2Normalize(temptr->Dir), Vector2Normalize({ -P1toP2.y, P1toP2.x }));
				thickness = 1.0f;
				color = RED;


				//need solution for when the laser leaves the obstacle and create new object and delete the old one
				if (!items.active){
					if (laser_manager.objectCount > 11) {

						break;
					}
					Vector2 start = { temptr->rayhit.point.x , temptr->rayhit.point.y };
					temp_Anchor = laser_manager.addLaser(start, Reflect, rayhits, thickness, color);

					items.active = true;
				}
				else {

					items.active = false;
				}

				break;
			}

			else {

				temptr->rayhit.hit = false;
			}
			//fix this shit its not detecting the correct change of id
			onHit = items.active;
			prevhit_id = items.Obstacle_id
		}*/