#include "bsepch.h"

bool CollisionFunctions2D::CheckCollisionCircleCircle(Shape* circle1, glm::vec3 c1Pos, Shape* circle2, glm::vec3 c2Pos, Contact* contact)
{
	return false;
}

bool CollisionFunctions2D::CheckCollisionCircleOBB(Shape* circle, glm::vec3 circlePos, Shape* obbShape, glm::vec3 obbPos, Contact* contact)
{
	return false;
}

bool CollisionFunctions2D::CheckCollisionCircleAABB(Shape* circleShape, glm::vec3 cPos, Shape* aabbShape, glm::vec3 rectPos, Contact* contact)
{
	return false;
}

bool CollisionFunctions2D::CheckCollisionAABBAABB(Shape* aabb1Shape, glm::vec3 aabb1Pos, Shape* aabb2Shape, glm::vec3 aabb2Pos, Contact* contact)
{
	AABB* aabb1 = static_cast<AABB*>(aabb1Shape);
	AABB* aabb2 = static_cast<AABB*>(aabb2Shape);

	glm::vec2 rect1Center = glm::vec2(aabb1Pos.x, aabb1Pos.y);
	glm::vec2 rect2Center = glm::vec2(aabb2Pos.x, aabb2Pos.y);

	float rect1Left = rect1Center.x + aabb1->Left;
	float rect1Right = rect1Center.x + aabb1->Right;
	float rect1Top = rect1Center.y + aabb1->Top;
	float rect1Bottom = rect1Center.y + aabb1->Bottom;

	float rect2Left = rect2Center.x + aabb2->Left;
	float rect2Right = rect2Center.x + aabb2->Right;
	float rect2Top = rect2Center.y + aabb2->Top;
	float rect2Bottom = rect2Center.y + aabb2->Bottom;

	if (rect1Left > rect2Right) return false;
	if (rect1Right < rect2Left) return false;
	if (rect1Top < rect2Bottom) return false;
	if (rect1Bottom > rect2Top) return false;

	contact->Bodies[0] = aabb1->body;
	contact->Bodies[1] = aabb2->body;

	return true;
}

bool CollisionFunctions2D::CheckCollisionAABBCircle(Shape* aabb1Shape, glm::vec3 aabb1Pos, Shape* aabb2Shape, glm::vec3 aabb2Pos, Contact* contact)
{
	return false;
}

bool CollisionFunctions2D::CheckCollisionAABBOBB(Shape* aabbShape, glm::vec3 aabbPos, Shape* obbShape, glm::vec3 obbPos, Contact* contact)
{

	return false;
}

bool CollisionFunctions2D::CheckCollisionOBBAABB(Shape* obbShape, glm::vec3 obbPos, Shape* aabbShape, glm::vec3 aabbPos, Contact* contact)
{
	OBB* obb = static_cast<OBB*>(obbShape);
	AABB* aabb = static_cast<AABB*>(aabbShape);

	obb->GenerateNormals();





	return false;
}

bool CollisionFunctions2D::CheckCollisionOBBCircle(Shape* obbShape, glm::vec3 obbPos, Shape* circle, glm::vec3 circlePos, Contact* contact)
{
	return false;
}

bool CollisionFunctions2D::CheckCollisionOBBOBB(Shape* obb1Shape, glm::vec3 obb1Pos, Shape* obb2Shape, glm::vec3 obb2Pos, Contact* contact)
{
	OBB* obb1 = static_cast<OBB*>(obb1Shape);
	OBB* obb2 = static_cast<OBB*>(obb2Shape);

	// 1. Get axes for each shape
	obb1->GenerateNormals();
	obb2->GenerateNormals();


	if (noGapExistsInAxis(obb1, obb2) && noGapExistsInAxis(obb2, obb1))
	{
		contact->Bodies[0] = obb1Shape->body;
		contact->Bodies[1] = obb2Shape->body;
		return true;
	}

	return false;
}

bool CollisionFunctions2D::noGapExistsInAxis(OBB* obbAxesOwner, OBB* obbOther)
{
	glm::vec3 obb_axis1 = obbAxesOwner->GetAxis1();
	glm::vec3 obb_axis2 = obbAxesOwner->GetAxis2();

	//// debug
	//// topleft vertex vector (from origin) + normal vector from topleft
	//glm::vec3 start = glm::vec3(obb1->TopLeft);
	//glm::vec3 end = (start + obb1_axis1);

	//PrimLine v1;
	//v1.Build(start, end);
	//v1.SetTranslate(glm::vec3(0.0f, 0.0f, 0.0f));
	//v1.Update();
	//v1.Draw();

	// 2. Projections 
	obb_axis1 = glm::normalize(obb_axis1);
	obb_axis2 = glm::normalize(obb_axis2);

	std::array<float, 4> projectionsOnAxis;
	std::array<float, 4> dots;
	float maxProjection, minProjection;

	//(use all vertices from OBB1 and OBB2)
		// OBB1 on Axis 1 
	dots[0] = glm::dot(glm::vec3(obbAxesOwner->TopLeft), obb_axis1);			// dot_v1_axis1
	dots[1] = glm::dot(glm::vec3(obbAxesOwner->TopRight), obb_axis1);			// dot_v2_axis1
	dots[2] = glm::dot(glm::vec3(obbAxesOwner->BottomRight), obb_axis1);		// dot_v3_axis1
	dots[3] = glm::dot(glm::vec3(obbAxesOwner->BottomLeft), obb_axis1);		// dot_v4_axis1 
	float obb1_min_axis1 = *std::min_element(dots.begin(), dots.end());
	float obb1_max_axis1 = *std::max_element(dots.begin(), dots.end());

	// OBB2 on Axis 1 
	dots[0] = glm::dot(glm::vec3(obbOther->TopLeft), obb_axis1);			// dot_v1_axis1
	dots[1] = glm::dot(glm::vec3(obbOther->TopRight), obb_axis1);			// dot_v2_axis1
	dots[2] = glm::dot(glm::vec3(obbOther->BottomRight), obb_axis1);		// dot_v3_axis1
	dots[3] = glm::dot(glm::vec3(obbOther->BottomLeft), obb_axis1);		// dot_v4_axis1 
	float obb2_min_axis1 = *std::min_element(dots.begin(), dots.end());
	float obb2_max_axis1 = *std::max_element(dots.begin(), dots.end());

	// OBB1 on Axis 2
	dots[0] = glm::dot(glm::vec3(obbAxesOwner->TopLeft), obb_axis2);			// dot_v1_axis2
	dots[1] = glm::dot(glm::vec3(obbAxesOwner->TopRight), obb_axis2);			// dot_v2_axis2
	dots[2] = glm::dot(glm::vec3(obbAxesOwner->BottomRight), obb_axis2);		// dot_v3_axis2
	dots[3] = glm::dot(glm::vec3(obbAxesOwner->BottomLeft), obb_axis2);		// dot_v4_axis2
	float obb1_min_axis2 = *std::min_element(dots.begin(), dots.end());
	float obb1_max_axis2 = *std::max_element(dots.begin(), dots.end());

	// OBB2 on Axis 2
	dots[0] = glm::dot(glm::vec3(obbOther->TopLeft), obb_axis2);			// dot_v1_axis2
	dots[1] = glm::dot(glm::vec3(obbOther->TopRight), obb_axis2);			// dot_v2_axis2
	dots[2] = glm::dot(glm::vec3(obbOther->BottomRight), obb_axis2);		// dot_v3_axis2
	dots[3] = glm::dot(glm::vec3(obbOther->BottomLeft), obb_axis2);		// dot_v4_axis2
	float obb2_min_axis2 = *std::min_element(dots.begin(), dots.end());
	float obb2_max_axis2 = *std::max_element(dots.begin(), dots.end());

	// projections on OBB1->axis 1
	projectionsOnAxis[0] = obb1_max_axis1;
	projectionsOnAxis[1] = obb1_min_axis1;
	projectionsOnAxis[2] = obb2_max_axis1;
	projectionsOnAxis[3] = obb2_min_axis1;
	maxProjection = *std::max_element(projectionsOnAxis.begin(), projectionsOnAxis.end());
	minProjection = *std::min_element(projectionsOnAxis.begin(), projectionsOnAxis.end());

	float distanceAMinMax_OBB1Axis1 = abs(obb1_max_axis1 - obb1_min_axis1);
	float distanceBMinMax_OBB1Axis1 = abs(obb2_max_axis1 - obb2_min_axis1);
	float distanceAminBMax_OBB1Axis1 = abs(maxProjection - minProjection);

	// projections on OBB1->Axis 2
	projectionsOnAxis[0] = obb1_max_axis2;
	projectionsOnAxis[1] = obb1_min_axis2;
	projectionsOnAxis[2] = obb2_max_axis2;
	projectionsOnAxis[3] = obb2_min_axis2;
	maxProjection = *std::max_element(projectionsOnAxis.begin(), projectionsOnAxis.end());
	minProjection = *std::min_element(projectionsOnAxis.begin(), projectionsOnAxis.end());

	float distanceAMinMax_OBB1Axis2 = abs(obb1_max_axis2 - obb1_min_axis2);
	float distanceBMinMax_OBB1Axis2 = abs(obb2_max_axis2 - obb2_min_axis2);
	float distanceAminBMax_OBB1Axis2 = abs(maxProjection - minProjection);







	if ((distanceAminBMax_OBB1Axis1 < distanceAMinMax_OBB1Axis1 + distanceBMinMax_OBB1Axis1) &&
		(distanceAminBMax_OBB1Axis2 < distanceAMinMax_OBB1Axis2 + distanceBMinMax_OBB1Axis2))
		return true;


	return false;
}

bool CollisionFunctions2D::noGapExistsInAxis(OBB* obbAxesOwner, AABB* aabbAxesOther)
{
	//glm::vec3 OtherTopLeft = glm::vec3(aabbAxesOther->Left, aabbAxesOther->Top, 0.0f);
	//glm::vec3 OtherTopRight = glm::vec3(aabbAxesOther->Right, aabbAxesOther->Top, 0.0f);
	//glm::vec3 OtherBottomLeft = glm::vec3(aabbAxesOther->Left, aabbAxesOther->Bottom, 0.0f);
	//glm::vec3 OtherBottomRight = glm::vec3(aabbAxesOther->Right, aabbAxesOther->Bottom, 0.0f);
	////glm::vec3 v1 = TopRight - TopLeft;
	////glm::vec3 v2 = TopLeft - BottomLeft;


	//glm::vec3 obb_axis1 = obbAxesOwner->GetAxis1();
	//glm::vec3 obb_axis2 = obbAxesOwner->GetAxis2();
	////glm::vec3 aabb_axis1 = glm::vec3(-v1.y, v1.x, 0.0f);
	////glm::vec3 aabb_axis2 = glm::vec3(-v2.y, v2.x, 0.0f);



	//// 2. Projections 
	//obb_axis1 = glm::normalize(obb_axis1);
	//obb_axis2 = glm::normalize(obb_axis2);

	//std::array<float, 4> projectionsOnAxis;
	//std::array<float, 4> dots;
	//float maxProjection, minProjection;

	////(use all vertices from OBB1 and OBB2)
	//	// OBB1 on Axis 1 
	//dots[0] = glm::dot(glm::vec3(obbAxesOwner->TopLeft), obb_axis1);			// dot_v1_axis1
	//dots[1] = glm::dot(glm::vec3(obbAxesOwner->TopRight), obb_axis1);			// dot_v2_axis1
	//dots[2] = glm::dot(glm::vec3(obbAxesOwner->BottomRight), obb_axis1);		// dot_v3_axis1
	//dots[3] = glm::dot(glm::vec3(obbAxesOwner->BottomLeft), obb_axis1);		// dot_v4_axis1 
	//float obb1_min_axis1 = *std::min_element(dots.begin(), dots.end());
	//float obb1_max_axis1 = *std::max_element(dots.begin(), dots.end());

	//// OBB2 on Axis 1 
	//dots[0] = glm::dot(glm::vec3(OtherTopLeft), obb_axis1);			// dot_v1_axis1
	//dots[1] = glm::dot(glm::vec3(OtherTopRight), obb_axis1);			// dot_v2_axis1
	//dots[2] = glm::dot(glm::vec3(OtherBottomRight), obb_axis1);		// dot_v3_axis1
	//dots[3] = glm::dot(glm::vec3(OtherBottomLeft), obb_axis1);		// dot_v4_axis1 
	//float obb2_min_axis1 = *std::min_element(dots.begin(), dots.end());
	//float obb2_max_axis1 = *std::max_element(dots.begin(), dots.end());

	//// OBB1 on Axis 2
	//dots[0] = glm::dot(glm::vec3(obbAxesOwner->TopLeft), obb_axis2);			// dot_v1_axis2
	//dots[1] = glm::dot(glm::vec3(obbAxesOwner->TopRight), obb_axis2);			// dot_v2_axis2
	//dots[2] = glm::dot(glm::vec3(obbAxesOwner->BottomRight), obb_axis2);		// dot_v3_axis2
	//dots[3] = glm::dot(glm::vec3(obbAxesOwner->BottomLeft), obb_axis2);		// dot_v4_axis2
	//float obb1_min_axis2 = *std::min_element(dots.begin(), dots.end());
	//float obb1_max_axis2 = *std::max_element(dots.begin(), dots.end());

	//// OBB2 on Axis 2
	//dots[0] = glm::dot(glm::vec3(OtherTopLeft), obb_axis2);			// dot_v1_axis2
	//dots[1] = glm::dot(glm::vec3(OtherTopRight), obb_axis2);			// dot_v2_axis2
	//dots[2] = glm::dot(glm::vec3(OtherBottomRight), obb_axis2);		// dot_v3_axis2
	//dots[3] = glm::dot(glm::vec3(OtherBottomLeft), obb_axis2);		// dot_v4_axis2
	//float obb2_min_axis2 = *std::min_element(dots.begin(), dots.end());
	//float obb2_max_axis2 = *std::max_element(dots.begin(), dots.end());

	//// projections on OBB1->axis 1
	//projectionsOnAxis[0] = obb1_max_axis1;
	//projectionsOnAxis[1] = obb1_min_axis1;
	//projectionsOnAxis[2] = obb2_max_axis1;
	//projectionsOnAxis[3] = obb2_min_axis1;
	//maxProjection = *std::max_element(projectionsOnAxis.begin(), projectionsOnAxis.end());
	//minProjection = *std::min_element(projectionsOnAxis.begin(), projectionsOnAxis.end());

	//float distanceAMinMax_OBB1Axis1 = abs(obb1_max_axis1 - obb1_min_axis1);
	//float distanceBMinMax_OBB1Axis1 = abs(obb2_max_axis1 - obb2_min_axis1);
	//float distanceAminBMax_OBB1Axis1 = abs(maxProjection - minProjection);

	//// projections on OBB1->Axis 2
	//projectionsOnAxis[0] = obb1_max_axis2;
	//projectionsOnAxis[1] = obb1_min_axis2;
	//projectionsOnAxis[2] = obb2_max_axis2;
	//projectionsOnAxis[3] = obb2_min_axis2;
	//maxProjection = *std::max_element(projectionsOnAxis.begin(), projectionsOnAxis.end());
	//minProjection = *std::min_element(projectionsOnAxis.begin(), projectionsOnAxis.end());

	//float distanceAMinMax_OBB1Axis2 = abs(obb1_max_axis2 - obb1_min_axis2);
	//float distanceBMinMax_OBB1Axis2 = abs(obb2_max_axis2 - obb2_min_axis2);
	//float distanceAminBMax_OBB1Axis2 = abs(maxProjection - minProjection);







	//if ((distanceAminBMax_OBB1Axis1 < distanceAMinMax_OBB1Axis1 + distanceBMinMax_OBB1Axis1) &&
	//	(distanceAminBMax_OBB1Axis2 < distanceAMinMax_OBB1Axis2 + distanceBMinMax_OBB1Axis2))
	//	return true;


	return false;
}
