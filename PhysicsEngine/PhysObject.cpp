#include "PhysObject.h"

#include "RayLib/raylib.h"

using std::string;
using glm::vec2;
PhysObject::PhysObject() {
	totalForces = vec2(0, 0);
	pos = vec2(0, 0);
	vel = vec2(0, 0);
	collider = Shape{ shapeType::NONE };
	mass = 1;
	gravity = vec2(0, 0);
}
PhysObject::PhysObject(float Mass,vec2 Gravity) : PhysObject() {
	
	mass = Mass;
	gravity = Gravity;

}
PhysObject::PhysObject(float Mass, vec2 Gravity, vec2 Pos) : PhysObject( Mass, Gravity) {
	totalForces = vec2(0, 0);
	pos = Pos;
	vel = vec2(0, 0);
	mass = Mass;
	gravity = Gravity;
}


void PhysObject::tickPhys(float delta) {
	addAccel(gravity);
	vel += totalForces*delta;
	pos += vel * delta;
	totalForces = vec2(0, 0);
}
void PhysObject::addForce(vec2 force) {
	vec2 accel = force / mass;
	totalForces += accel;
}
void PhysObject::addAccel(vec2 force) {
	totalForces += force;
}
void PhysObject::addVel(vec2 force) {
	vel += force;
}
void PhysObject::addImpulse(vec2 force) {
	vec2 momentum = force/mass;
	vel += momentum;
}

void PhysObject::draw() const {
	switch (collider.type) {
	case shapeType::NONE:
		DrawPixel(pos.x, pos.y, RED);
		break;
	case shapeType::CIRCLE:
		DrawCircle(pos.x, pos.y, collider.circleData.radius, RED);
		break;

	case shapeType::AABB:
		DrawRectangle(pos.x, pos.y, collider.rectData.extents.x, collider.rectData.extents.y,RED);
		break;

	default:
		break;
	}
}


