#include "Shape.h"

bool checkCircleCircle(const glm::vec2& posA, const Shape& shapeA, const glm::vec2& posB, const Shape& shapeB) {
	glm::vec2 offset = posA - posB;
	float distance = glm::length(offset);
	float radiusSum = shapeA.circleData.radius + shapeB.circleData.radius;
	return distance < radiusSum;
}
bool checkAABBAABB(const glm::vec2& posA, const Shape& shapeA, const glm::vec2& posB, const Shape& shapeB) {
	glm::vec2 aMin = posA;
	glm::vec2 aXMax = glm::vec2(posA.x + shapeA.rectData.extents.x, posA.y);
	glm::vec2 aYMax = glm::vec2(posA.x, posA.y + shapeA.rectData.extents.y);
	glm::vec2 aMax = glm::vec2(aXMax.x, aYMax.y);

	glm::vec2 bMin = posB;
	glm::vec2 bXMax = glm::vec2(posB.x + shapeB.rectData.extents.x, posB.y);
	glm::vec2 bYMax = glm::vec2(posB.x, posB.y + shapeB.rectData.extents.y);
	glm::vec2 bMax = glm::vec2(bXMax.x, bYMax.y);

	return aMin.x < bMax.x &&
		aMax.x > bMin.x &&
		aMin.y < bMax.y &&
		aMax.y > bMin.y;
}
bool checkCircAABB(glm::vec2 circPos, Circle circle, glm::vec2 rectPos, AABB rect) {
	glm::vec2 rectMax = rectPos + rect.extents;
	glm::vec2 clampVect = glm::clamp(circPos, rectPos, rectMax);
	return glm::distance(clampVect, circPos) < circle.radius;
}
bool checkCircAABB(const glm::vec2& posA, const Shape& shapeA, const glm::vec2& posB, const Shape& shapeB){
	glm::vec2 rectMax = posB + shapeB.rectData.extents;
	glm::vec2 clampVect = glm::clamp(posA, posB, rectMax);
	return glm::distance(clampVect, posA) < shapeA.circleData.radius;
}

glm::vec2 depenetrateCircleCircle(const glm::vec2& posA, const Shape& shapeA, const glm::vec2& posB, const Shape& shapeB, float& pen)
{
	glm::vec2 offset = posA - posB;
	float dist = glm::length(offset);
	float sum = shapeA.circleData.radius + shapeB.circleData.radius;

	//write the penetration depth
	pen = sum - dist;
	//return collision normal
	return glm::normalize(offset);
}
glm::vec2 depenetrateAABBAABB(const glm::vec2& posA, const Shape& rectA, const glm::vec2& posB, const Shape& rectB, float& pen){
	
	glm::vec2 aMin = posA;
	glm::vec2 aXMax = glm::vec2(posA.x + rectA.rectData.extents.x, posA.y);
	glm::vec2 aYMax = glm::vec2(posA.x, posA.y + rectA.rectData.extents.y);
	glm::vec2 aMax = glm::vec2(aXMax.x, aYMax.y);
	glm::vec2 aHalfExt = rectA.rectData.extents / 2.0f;
	glm::vec2 aMid = posA + aHalfExt;

	glm::vec2 bMin = posB;
	glm::vec2 bXMax = glm::vec2(posB.x + rectB.rectData.extents.x, posB.y);
	glm::vec2 bYMax = glm::vec2(posB.x, posB.y + rectB.rectData.extents.y);
	glm::vec2 bMax = glm::vec2(bXMax.x, bYMax.y);
	glm::vec2 bHalfExt = rectB.rectData.extents / 2.0f;
	glm::vec2 bMid = posB + bHalfExt;
	
	//x penetration
	float xDist = glm::distance(aMid.x, bMid.x);
	//y penetration
	float yDist = glm::distance(aMid.y, bMid.y);

	float xOverlap = aHalfExt.x + bHalfExt.x - xDist;
	float yOverlap = bHalfExt.y + bHalfExt.y - yDist;
	//compute which axis is shorter
	if (xOverlap < yOverlap) {
		//depen the x axis
		float sum = aHalfExt.x + bHalfExt.x;
		pen = sum - xDist;
	}
	else {
		//depen the y axis
		float sum = aHalfExt.y + bHalfExt.y;
		pen = sum - yDist;
	}

	//get the normal between them???
	return glm::normalize(aMid - bMid);
}
glm::vec2 depenetrateCircAABB(const glm::vec2& posA, const Shape& circle, const glm::vec2& posB, const Shape& rect, float&pen) {
	glm::vec2 rectMax = posB + rect.rectData.extents;
	glm::vec2 clampVect = glm::clamp(posA, posB, rectMax);
	pen = circle.circleData.radius - glm::distance(clampVect, posA);
	glm::vec2 offset = posA - clampVect;

	//edge case for when circle center is inside rectangle
	if (clampVect == posA) {
		glm::vec2 rectCenter = posB + (rect.rectData.extents / 2.0f);
		offset = posA - rectCenter;
	}
	return glm::normalize(offset);
}

