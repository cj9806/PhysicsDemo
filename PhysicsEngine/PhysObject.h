#pragma once
#include"GLM/glm.hpp"
#include <string>
#include "Shape.h"
using std::string;

using glm::vec2;
class PhysObject
{
private:
	vec2 totalForces;
public:
	//objects position
	vec2 pos;
	//objects velocity
	vec2 vel;
	//objects mass
	float mass;
	vec2 gravity;//defaults to 0,0
	Shape collider;

	PhysObject();
	//Initializes pos and vel to defaults of (0,0)
	PhysObject(float Mass, vec2 Gravity);
	PhysObject(float Mass, vec2 Gravity, vec2 Pos);
	//integrates velocity into position with provied time step given the delta time
	void tickPhys(float delta);

	//accepts a vector2 describing the force on the object
	void addForce(vec2 force); // increments total force with respects to mass
	
	void addAccel(vec2 force);// increments total force without respects to mass
	void addVel(vec2 force);// increments velocity without respects to mass
	void addImpulse(vec2 force);// increments velocity with respects to mass

	void draw() const;
};

float resolveCollision(vec2 posA, vec2 velA, float massA,
					  vec2 posB, vec2 velB, float massB,
					  float elasticity, vec2 normal);

void resolvePhysBodies(PhysObject& lhs, PhysObject& rhs, float elasticity, const glm::vec2& normal, float& pen);
