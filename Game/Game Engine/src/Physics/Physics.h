#pragma once

#define GRAVITY -1.0f

#define MAX_VELOCITY 10.0f
#define MIN_VELOCITY -MAX_VELOCITY

struct PhysicsObj
{

	bool	collision;

	vec2	position;
	vec2	acceration;
	vec2	velocity;
};


