#include "Simulation.h"

float runningTime = 1.0f / 12.0f;
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
			//Fix it so when the anchor laser moves the other parts moves too :HOW TO FUCKING DO THIS
			if (collisionChecker.DetectCollision(ObstaclesStorage[obstacle], temptr)) {
				PoI = collisionChecker.PointOfIntersection(ObstaclesStorage[obstacle].Obstacle_P1, ObstaclesStorage[obstacle].Obstacle_P2, collisionChecker.t, collisionChecker.u);
				thickness = 1.0f;
				color = RED;
				rayhits.point.x = PoI.x;
				rayhits.point.y = PoI.y;
				rayhits.hit = false;
				
				temptr->rayhit.hit = true;
				temptr->currhit_id = ObstaclesStorage[obstacle].Obstacle_id;
				temptr->rayhit.point.x = PoI.x;
				temptr->rayhit.point.y = PoI.y;
			
				P1toP2 = { ObstaclesStorage[obstacle].Obstacle_P2.x - ObstaclesStorage[obstacle].Obstacle_P1.x, ObstaclesStorage[obstacle].Obstacle_P2.y - ObstaclesStorage[obstacle].Obstacle_P1.y };
				Reflect = Vector2Reflect(Vector2Normalize(temptr->Dir), Vector2Normalize({ -P1toP2.y, P1toP2.x }));
				std::cout << " Current State of the obstacle: " << ObstaclesStorage[obstacle].active << "\n";

				//need solution for when the laser leaves the obstacle and create new object and delete the old one
				if (!ObstaclesStorage[obstacle].active || temp_Anchor->next == nullptr) {
					//std::cout << "current prev Values-> " << prev_Values.back() << "\n";
					if (laser_manager.objectCount > 11) {
						break;
					}
					//with the changes on deleting its not properly spawning new object
					Vector2 start = { temptr->rayhit.point.x , temptr->rayhit.point.y };
					temp_Anchor = laser_manager.addLaser(start, Reflect, rayhits, thickness, color);
					ObstaclesStorage[obstacle].active = true;

				}
				else{
					/*if (onHit) {
						ObstaclesStorage[obstacle].active = false;
					}*/
					
					ObstaclesStorage[obstacle].active = false;
				}
				break;
			}else {
				temptr->currhit_id = 0;
				temptr->rayhit.hit = false;
			}
			if (temptr != nullptr) {
				if (temp_Anchor->rayhit.hit == false) {
					laser_manager.deleteLaser(temp_Anchor);
					std::cout << "\nDelete\n";
					std::cout << "\nObject Count: " << laser_manager.objectCount << "\n";
				}
				laser_manager.DeleteInChange(temp_Anchor->currhit_id, prevhit_id, temp_Anchor);
				std::cout << "\nObject Count on change of collision: " << laser_manager.objectCount << "\n";
			
			}
		}
	
		temptr = temptr->next;
		
	} while (temptr != nullptr);
}



void Simulation::DrawSimulation()
{
	
	
	for (auto& items: ObstaclesStorage) {

		items.Draw();
	}
	laser_manager.Draw();
}

void Simulation::DetectChangeCollision()
{
	//solve this tomorrow

	if (temp_Anchor->currhit_id != prev_Values.back() && !prev_Values.empty()) {
		
		std::cout << " change of ID\n";
		onHit = true;
		prevhit_id = prev_Values.back();

	}
	else {
		onHit = false;
		
	}
	if (prev_Values.size() > 13) {
		prev_Values.erase(prev_Values.begin());
	}
	else {
		prev_Values.push_back(temp_Anchor->currhit_id);
	}
	
	
	std::cout << "Anchor current hit ID-> " << temp_Anchor->currhit_id << "Previous Hit-> " << prevhit_id << "\n";
	std::cout << "Anchor actual ID-> " << temp_Anchor->id << "\n";

}


void Simulation::MovementSimulation()
{
	laser_manager.AnchorMovement();
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
	Vector2 P3Checker = { 200.0f, 300.0f };
	Vector2 P4Checker = { 200.0f, 500.0f };
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