#include "Collision.h"

Collision::Collision()
	:
	Lasermanager()
{
}

void Collision::DetectCollision(LaserManager& Lasermanager)
{
}



/*IntersectingLines(Obstacle::Plane obs, Ray& laser)
{
	const float x1 = obs.P1.x;
	const float y1 = obs.P1.y;
	const float x2 = obs.P2.x;
	const float y2 = obs.P2.y;

	float x3 = laser.position.x;
	float y3 = laser.position.y;
	float x4 = laser.position.x + laser.direction.x;
	float y4 = laser.position.y + laser.direction.y;


	const float denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	if (denominator == 0) {
		return false;
	}

	t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denominator;

	u = -(((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denominator);

	if (t >= 0 && t <= 1 && u > 1) {

		return true;

	}
	else {
		return false;
	}

}


//returns the point of intersection
Vector3 Collision::IntersectPoint(Vector2 p1, Vector2 p2, float t, float u)
{
	Vector3 pointofintersect = { 0 };

	pointofintersect.x = p1.x + t * (p2.x - p1.x);
	pointofintersect.y = p1.y + t * (p2.y - p1.y);
	pointofintersect.z = 0.0f;

	return pointofintersect;
}*/