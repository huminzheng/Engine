#pragma once

#include <vector>
#include "BoxConfig.h"
#include "Particle.h"
#include "../Constraint.h"

class Box
{
public:
	Box();
	~Box();
	float mass;
	vec3 dimensions, center_pos;
	vec3 num_particles;

	std::vector<Particle> particles;
	std::vector<Constraint*> constraints;
};


Box *make_box(BoxConfig * const config);
