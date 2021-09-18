#include "Shape.h"
bool checkCircleCircle(glm::vec2 posA, Circle circleA, glm::vec2 posB, Circle circleB) {
	glm::vec2 offset = posA - posB;
	float distance = glm::length(offset);
	float radiusSum = circleA.radius + circleB.radius;
	return distance < radiusSum;
}
bool checkCircleCircle(const glm::vec2& posA, const Shape& shapeA, const glm::vec2& posB, const Shape& shapeB) {
	return checkCircleCircle(posA, shapeA.circleData, posB, shapeB.circleData);
}
bool checkAABBAABB(glm::vec2 posA, AABB rectA, glm::vec2 posB, AABB rectB) {
	glm::vec2 aMin = posA;
	glm::vec2 aXMax = glm::vec2(posA.x + rectA.extents.x, posA.y);
	glm::vec2 aYMax = glm::vec2(posA.x, posA.y + rectA.extents.y);
	glm::vec2 aMax = glm::vec2(aXMax.x, aYMax.y);

	glm::vec2 bMin = posB;
	glm::vec2 bXMax = glm::vec2(posB.x + rectB.extents.x, posB.y);
	glm::vec2 bYMax = glm::vec2(posB.x, posB.y + rectB.extents.y);
	glm::vec2 bMax = glm::vec2(bXMax.x, bYMax.y);

	return aMin.x < bMax.x &&
		   aMax.x > bMin.x &&
		   aMin.y < bMax.y &&
		   aMax.y > bMin.y;
}
bool checkAABBAABB(const glm::vec2& posA, const Shape& shapeA, const glm::vec2& posB, const Shape& shapeB) {
	return checkAABBAABB(posA, shapeA.rectData, posB, shapeB.rectData);
}
bool checkCircAABB(glm::vec2 circPos, Circle circle, glm::vec2 rectPos, AABB rect) {
	glm::vec2 rectMax = rectPos + rect.extents;
	glm::vec2 clampVect = glm::clamp(circPos, rectPos, rectMax);
	return glm::distance(clampVect, circPos) < circle.radius;
}
bool checkCircAABB(const glm::vec2& posA, const Shape& shapeA, const glm::vec2& posB, const Shape& shapeB){
	return checkCircAABB(posA, shapeA.circleData, posB, shapeB.rectData);
}
