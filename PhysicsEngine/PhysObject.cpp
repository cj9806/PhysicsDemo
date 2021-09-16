#include "PhysObject.h"
using std::string;
using glm::vec2;
PhysObject::PhysObject(float Mass,vec2 Gravity) {
	totalForces = vec2(0, 0);
	pos = vec2(0, 0);
	vel = vec2(0, 0);
	mass = 1.0f;
	gravity = vec2(0,0);
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


