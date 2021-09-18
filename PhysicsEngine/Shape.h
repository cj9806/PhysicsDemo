#pragma once
#include <cstdint>
#include"GLM/glm.hpp"
struct Circle {
	float radius;
};
struct AABB{
	glm::vec2 extents;
};

enum class shapeType : uint8_t {
	NONE = 0,
	CIRCLE = 1 << 0,
	AABB = 1<<1

};
struct Shape {
	shapeType type;

	union {
		Circle circleData;
		AABB rectData;
	};
};

bool checkCircleCircle(glm::vec2 posA, Circle circleA, glm::vec2 posB, Circle circleB);
bool checkCircleCircle(const glm::vec2& posA, const Shape& shapeA, const glm::vec2& posB, const Shape& shapeB);
bool checkAABBAABB(glm::vec2 posA, AABB rectA, glm::vec2 posB, AABB rectB);
bool checkAABBAABB(const glm::vec2& posA, const Shape& shapeA, const glm::vec2& posB, const Shape& shapeB);
bool checkCircAABB(glm::vec2 circPos, Circle circle, glm::vec2 rectPos, AABB rect);
bool checkCircAABB(const glm::vec2& posA, const Shape& shapeA, const glm::vec2& posB, const Shape& shapeB);
