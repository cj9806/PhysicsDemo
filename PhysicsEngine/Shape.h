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

bool checkCircleCircle(const glm::vec2& posA, const Shape& shapeA, const glm::vec2& posB, const Shape& shapeB);
bool checkAABBAABB(const glm::vec2& posA, const Shape& shapeA, const glm::vec2& posB, const Shape& shapeB);
bool checkCircAABB(const glm::vec2& posA, const Shape& shapeA, const glm::vec2& posB, const Shape& shapeB);

glm::vec2 depenetrateCircleCircle(const glm::vec2& posA, const Shape& shapeA, const glm::vec2& posB, const Shape& shapeB, float& pen);
glm::vec2 depenetrateAABBAABB(const glm::vec2& posA, const Shape& rectA, const glm::vec2& posB, const Shape& rectB, float& pen);
glm::vec2 depenetrateCircAABB(const glm::vec2& posA, const Shape& circle, const glm::vec2& posB, const Shape& rect, float& pen);