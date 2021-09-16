#pragma once
#include"GLM/glm.hpp"
#include <string>
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

	//Initializes pos and vel to defaults of (0,0)
	PhysObject(float Mass, vec2 Gravity);

	//integrates velocity into position with provied time step given the delta time
	void tickPhys(float delta);

	//accepts a vector2 describing the force on the object
	void addForce(vec2 force); // increments total force with respects to mass
	
	void addAccel(vec2 force);// increments total force without respects to mass
	void addVel(vec2 force);// increments velocity without respects to mass
	void addImpulse(vec2 force);// increments velocity with respects to mass
};

