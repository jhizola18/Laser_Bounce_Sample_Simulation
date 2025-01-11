#include "Collision.h"

Collision::Collision()
	:
	Lasermanager()
{
	t = 0.0f;
	u = 0.0f;
}
//create a well structured collision detection for the ray and the obstacles
/*Study the line intersection please or at least how it works*/
/*Also the reflection formula where Vreflect = d - 2(scalarproj) * Normal*/
bool Collision::DetectCollision(Obstacle& obs, Laser* &laser)
{
	if (IntersectingLines(obs, laser)) {
		return true;
	}
	else {
		return false;
	}
	
}

bool Collision::IntersectingLines(Obstacle& obs, Laser* &laser)
{
	const float x1 = obs.Obstacle_P1.x;
	const float y1 = obs.Obstacle_P1.y;
	const float x2 = obs.Obstacle_P2.x;
	const float y2 = obs.Obstacle_P2.y;

	float x3 = laser->StartPos.x;
	float y3 = laser->StartPos.y;
	float x4 = laser->StartPos.x + laser->Dir.x;
	float y4 = laser->StartPos.y + laser->Dir.y;

	const float denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	
	if (denominator == 0) {

		return false;
	
	}

	t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denominator;

	u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denominator;

	if (t >= 0 && t <= 1 && u > 1) {
		
		return true;
	}
	else {

		return false;
	}
}

//return the value of point of intersection 
Vector2 Collision::PointOfIntersection(Vector2 P1, Vector2 P2, float t , float u) {

	Vector2 pointOfIntersection = {0};

	pointOfIntersection.x = P1.x + t * (P2.x - P1.x);
	pointOfIntersection.y = P1.y + t * (P2.y - P1.y);

	return pointOfIntersection;


}

/*

//returns the point of intersection
Vector3 Collision::IntersectPoint(Vector2 p1, Vector2 p2, float t, float u)
{
	Vector3 pointofintersect = { 0 };

	pointofintersect.x = p1.x + t * (p2.x - p1.x);
	pointofintersect.y = p1.y + t * (p2.y - p1.y);
	pointofintersect.z = 0.0f;

	return pointofintersect;
}*/