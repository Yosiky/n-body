#include "planet.h"

PlanetConfig::PlanetConfig(void) 
	:	mass_min(0.01),
		mass_max(1) { }

PlanetConfig::~PlanetConfig(void) { }

CubePlanetConfig::CubePlanetConfig(void)
	:	PlanetConfig(), len(1) { }

void CubePlanetConfig::gen_position(vec3 *pos) const {

	std::random_device rd;
	std::mt19937 gen(time(0));
	std::uniform_real_distribution<real_type> unif_d(-len, len);

	for (int i = 0; i < 3; ++i) {
    	pos->array[i] = unif_d(gen);
	}
}

void CubePlanetConfig::gen_speed(vec3 *speed) const {
	
	std::random_device rd;
	std::mt19937 gen(time(0));
	std::uniform_real_distribution<real_type> unif_d(-1.0, 1.0);

	for (int i = 0; i < 3; ++i) {
		speed->array[i] = unif_d(gen) * 1.0e-1f;
	}
}

void CubePlanetConfig::gen_acceleration(vec3 *acc) const {
	for (int i = 0; i < 3; ++i) {
		acc->array[i] = 0.f;
	}
}

void CubePlanetConfig::gen_mass(real_type *mass) const {

	std::random_device rd;
	std::mt19937 gen(time(0));
	std::uniform_real_distribution<real_type> unif_d(mass_min, mass_max);

	*mass = unif_d(gen);
}
