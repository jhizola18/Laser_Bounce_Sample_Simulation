#include "Simulation.h"

Simulation::Simulation()
	:
	laser_manager(),
	collisionChecker()
{
	ObstaclesStorage = ShapeCreation();
	prevhit_id = 0;
	currhit_id = 0;
	onHit = false;
}

void Simulation::MainSimulation() 
{
	Laser* temptr = laser_manager.GetAnchor_Laser();
	Vector2 PoI = { 0 };
	Vector2 P1toP2 = { 0 };
	Vector2 Reflect = { 0 };
	RayCollision rayhits = { 0 };
	float thickness = 0.0f;
	Color color = WHITE;
	//create a delete node if there is no collision and find out why its not following the main anchor 
	do {
		
		if (temptr == NULL) {
			std::cout << "NULL";
			break;
		}
			for (auto& items : ObstaclesStorage) {
				
					if (collisionChecker.DetectCollision(items, temptr)) {
						if (!items.active) {
							temptr->rayhit.hit = true;
							std::cout << "\nHit\n";
							PoI = collisionChecker.PointOfIntersection(items.Obstacle_P1, items.Obstacle_P2, collisionChecker.t, collisionChecker.u);
							temptr->rayhit.point.x = PoI.x;
							temptr->rayhit.point.y = PoI.y;
							P1toP2 = { items.Obstacle_P2.x - items.Obstacle_P1.x, items.Obstacle_P2.y - items.Obstacle_P1.y };
							DrawCircleV(PoI, 3.0f, GREEN);
							Reflect = Vector2Reflect(temptr->Dir, Vector2Normalize({ -P1toP2.y, P1toP2.x }));
							rayhits.hit = false;
							thickness = 1.0f;
							color = RED;
							temptr->id = items.Obstacle_id;
							temptr->rayhit.hit = true;
							if (laser_manager.objectCount >= 5) {
								break;
							}
							laser_manager.SetAnchor_Laser(laser_manager.addLaser(0, PoI, Reflect, rayhits, thickness, color));
							items.active = true;
							//the id system is now working;
							std::cout << "\n currID:" << currhit_id << "\n";
							std::cout << "\n prevID:" << prevhit_id << "\n";
							prevhit_id = currhit_id;
							
						}
						else {
							
							items.active = false;
						}
						break;
					
					}
					else {
						std::cout << "No Collision";
					}

			}
		
		std::cout << "Next";
		temptr = temptr->next;
	} while (temptr != NULL);
	std::cout << "END of loop\n";
	//why its not making object here????
	std::cout << "\prevhit: " << prevhit_id << "\n";
	std::cout << "\currhit: " << currhit_id << "\n";
	/*if (prevhit_id != currhit_id && onHit) {
		std::cout << "\nNew Node added to the list\n";
		laser_manager.SetAnchor_Laser(laser_manager.addLaser(0, PoI, Reflect, rayhits, thickness, color));
		prevhit_id = currhit_id;
		onHit = false;
	}
	else {
		std::cout << "\nAlready collided:\n";
	}*/
	
	
	
}

void Simulation::DrawSimulation()
{
	laser_manager.Draw();
	
	for (auto& items: ObstaclesStorage) {

		items.Draw();
	}
	
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
