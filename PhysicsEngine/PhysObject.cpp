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

float resolveCollision(vec2 posA, vec2 velA, float massA, 
	vec2 posB, vec2 velB, float massB, 
	float elasticity, vec2 normal)
{
	//calculate relative velocity
	vec2 relVel = velA - velB;
	//calculate impulse magnitude to apply
	float impulseMag = glm::dot(-(1.0f + elasticity) * relVel, normal) /
					   glm::dot(normal, normal * (1 / massA + 1 / massB));

	return impulseMag;
}

void resolvePhysBodies(PhysObject &lhs, PhysObject &rhs, float elasticity, const glm::vec2 &normal, float& pen){
	//calculate our resolution impulse
	float impluseMagnitude = resolveCollision(lhs.pos, lhs.vel, lhs.mass,
											  rhs.pos, rhs.vel, rhs.mass,
											  elasticity, normal);
	vec2 impulse = impluseMagnitude * normal;
	//depenetrate the objects
	pen *= .51;
	//apply resolution forces/impulses to both objects
	vec2 correction = normal * pen;
	lhs.pos += correction;
	lhs.addImpulse(impulse);
	rhs.pos -= correction;
	rhs.addImpulse(-impulse);
}
