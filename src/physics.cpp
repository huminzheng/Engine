#include "physics.h"
#include <stdio.h>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>



#ifndef WORLD_MIN
#define WORLD_MIN vec3(-20.f,-20.f,-20.f)
#define WORLD_MAX vec3( 20.f, 20.f, 20.f)
#endif // !WORLD_MIN
namespace physics {

void simulate(std::vector<Particle> &particles, std::vector<Constraint*> &constraints, Scene *scene, float dt, int iterations)
{
	/* Based on 2007 PBD, NOT Unified Framework */

	const float GRAVITY = 4.0f;
	for (std::vector<glm::vec3>::size_type i = 0; i != particles.size(); i++) {
		/*
		* For all particles i
		* Apply forces			v_i = v_i + dt * f_ext(x_i)
		* Damp velocities		-- Skip for now -- TODO --
		* Predict position		x_i^* = x_i + dt * v_i
		*/
		particles[i].velocity = particles[i].velocity - glm::vec3(0.f, dt * GRAVITY, 0.f) * particles[i].invmass; // Gravity
		particles[i].pPos = particles[i].pos + dt * particles[i].velocity; // symplectic Euler 
		// ******************************************************************************************************************

		// For all particles i
		// Generate collision constraints
		/*
		* Add constraints from collisions to already given list of constraints
		*/
		// TODO
		// Temporary collision check and handler for some plane
		/*if (particles[i].pPos.y < -10) {
			particles[i].pPos.y = -10;
		}*/
        particles[i].pPos = min(max(WORLD_MIN, particles[i].pPos), WORLD_MAX);
		// ******************************************************************************************************************
	}

	// For all particles i
	// Generate collision constraints
	/* Add constraints from collisions to already given list of constraints */
    for (unsigned int i = 0; i != particles.size(); i++)
    {
            
        // Check collisions with scene
        for (unsigned int t = 0; t < scene->indices.size(); t+=3) 
        {

            vec3 v0 = vec3(scene->vertexes[3 * scene->indices[t]],
                            scene->vertexes[3 * scene->indices[t] + 1],
                            scene->vertexes[3 * scene->indices[t] + 2]);

            vec3 v1 = vec3(scene->vertexes[3 * scene->indices[t+1]],
                            scene->vertexes[3 * scene->indices[t+1] + 1],
                            scene->vertexes[3 * scene->indices[t+1] + 2]);

            vec3 v2 = vec3(scene->vertexes[3 * scene->indices[t+2]],
                            scene->vertexes[3 * scene->indices[t+2] + 1],
                            scene->vertexes[3 * scene->indices[t+2] + 2]);

            Intersection isect;
            if (intersect(v0, v1, v2, particles[i].pPos, PARTICLE_RADIUS,isect))
            {
                particles[i].pPos += isect.response;
            }
        }

        // Check collisions with other particles
        for (unsigned int j = 0; j < i; j++) 
        {
            Intersection isect;
            
            if (particles[i].phase != particles[j].phase && intersect(
                particles[i].pPos, particles[i].invmass,
                particles[j].pPos, particles[j].invmass,
                isect)
            ) {
                particles[i].pPos += isect.point;
                particles[j].pPos += isect.response;
            }
        }
            


    }
	/* 
	 * Stationary iterative linear solver - Gauss-Seidel 
	 */

	for (int i = 0; i < iterations; i++)
	{

		for (Constraint *c : constraints)
		{
			if (c->evaluate())
			{ 
				for (std::vector<Particle*>::iterator p = c->particles.begin(); p != c->particles.end(); p++)
				{
					// delta p_i = -w_i * s * grad_{p_i} C(p) * stiffness correction 
					(*p)->pPos -= (*p)->invmass * c->evaluateScaleFactor() * c->evaluateGradient(p) * (1 - pow(1 - c->stiffness, 1/(float)i));
				}
			}
		}
	}







	// For all particles i
	// v_i = (x_i^* - x_i) / dt
	// x_i = x_i^*

	for (std::vector<glm::vec3>::size_type i = 0; i != particles.size(); i++) 
	{
		/*
		* For all particles i
		* v_i = (x_i^* - x_i) / dt
		* x_i = x_i^*
		*/
		particles[i].velocity = (particles[i].pPos - particles[i].pos) / dt;
		// rough attempt at particle sleeping implementation in order to make particles stay in one place - most likely needs proper friction to work
		if (glm::length(particles[i].pos - particles[i].pPos) > 0.01)
			particles[i].pos = particles[i].pPos;
		// ***************************************************************************************************************************

		/*
		* Update velocities according to friction and restituition coefficients
		*/
		// Naive friction implementation
		if (particles[i].pos.y <= -10) {
			particles[i].velocity.z *= 0.4f;
			particles[i].velocity.x *= 0.4f;
		}
	}
		// Update velocities according to friction and restituition coefficients
		/* Skip this for now */
	
	
}

			
}
