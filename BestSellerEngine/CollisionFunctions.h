#pragma once
#include "bsepch.h"
class CollisionFunctions2D
{
public:
	CollisionFunctions2D() {}
	~CollisionFunctions2D() {}


	static bool CheckCollisionCircleAABB(Shape* circleShape, glm::vec3 cPos,
		Shape* aabbShape, glm::vec3 rectPos, Contact* contact);

	static bool CheckCollisionCircleCircle(Shape* circle1, glm::vec3 c1Pos,
		Shape* circle2, glm::vec3 c2Pos, Contact* contact);

	static bool CheckCollisionCircleOBB(Shape* circle, glm::vec3 circlePos,
		Shape* obbShape, glm::vec3 obbPos, Contact* contact);



	static bool CheckCollisionAABBAABB(Shape* aabb1Shape, glm::vec3 aabb1Pos,
		Shape* aabb2Shape, glm::vec3 aabb2Pos, Contact* contact);

	static bool CheckCollisionAABBCircle(Shape* aabb1Shape, glm::vec3 aabb1Pos,
		Shape* aabb2Shape, glm::vec3 aabb2Pos, Contact* contact);

	static bool CheckCollisionAABBOBB(Shape* aabbShape, glm::vec3 aabbPos,
		Shape* obbShape, glm::vec3 obbPos, Contact* contact);



	static bool CheckCollisionOBBAABB(Shape* obbShape, glm::vec3 obbPos,
		Shape* aabbShape, glm::vec3 aabbPos, Contact* contact);

	static bool CheckCollisionOBBCircle(Shape* obbShape, glm::vec3 obbPos,
		Shape* circle, glm::vec3 circlePos, Contact* contact);

	static bool CheckCollisionOBBOBB(Shape* obb1Shape, glm::vec3 obb1Pos,
		Shape* obb2Shape, glm::vec3 obb2Pos, Contact* contact);

private:

	static bool noGapExistsInAxis(OBB* obbAxesOwner, OBB* obbOther);
	static bool noGapExistsInAxis(OBB* obbAxes, AABB* aabbAxes);

};