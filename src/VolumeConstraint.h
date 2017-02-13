#pragma once
#include "Constraint.h"
#include "Particle.h"

class VolumeConstraint :
	public Constraint
{
public:
	float volume;

	VolumeConstraint(Particle* p1, Particle* p2, float stiffness, float volume, bool equality = true) {
		this->particles.push_back(p1);
		this->particles.push_back(p2);
		this->stiffness = stiffness;
		this->volume = volume;
		this->equality = equality;
	}

	bool evaluate() {
		return equality || 1 < 0;
	}

	float evaluateScaleFactor() {
		return 0.0f;
	}

	float3 evaluateGradient(std::vector<Particle*>::iterator p) {
		return float3();
	}

};

