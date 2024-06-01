#include "simulation.h"

void Simulation::log(const char *str) const {
	if (verbosity)
		std::cout << str << std::endl;
}

void Simulation::log_error(const char *str) const {
	std::cerr << "Error: " << str << std::endl;
	exit(1);
}

void Simulation::calc_time_step(void) {
	log(__func__);

	if (iter_count == 0) {
		log_error("iter_count == 0");
	}
	time_step = (real_type)sim_time / iter_count;
}

void Simulation::init_planet(void) { 

	for (int i = 0; i < count_planet; ++i) {
		planet_config->gen_position(&bodies[i].pos);
		planet_config->gen_speed(&bodies[i].speed);
		planet_config->gen_acceleration(&bodies[i].acceleration);
		planet_config->gen_mass(&bodies[i].mass);
	}
}

Simulation::Simulation(int _count_planet, int _iter_count, int _sim_time, PlanetConfig *_planet_config, bool _verbosity)
	:	planet_config(_planet_config),
		count_planet(_count_planet),
		iter_count(_iter_count),
		sim_time(_sim_time), 
		verbosity(_verbosity) {

	log(__func__);
	if (count_planet < 0 || iter_count < 0 || sim_time < 0) {
		log_error("one argument is negative");
	}
	calc_time_step();
}

static void sum_with_correction(real_type &sum, real_type &value_to_add, real_type &correction)
{
  real_type corrected = value_to_add - correction;
  real_type new_sum = sum + corrected;
  correction = (new_sum - sum) - corrected;
  sum = new_sum;
}

static constexpr double softeningSquared = 1e-9;
static constexpr double G = 6.67259e-11;

static real_type compute_k_energy(Planet *planets, int num_parts) {

	real_type energy = 0.;
	real_type correction = 0.;

	for (int i = 0; i < num_parts; ++i) {
		real_type curr_energy = planets[i].mass * (planets[i].speed.array[0] * planets[i].speed.array[0] + 
												 planets[i].speed.array[1] * planets[i].speed.array[1] +
												 planets[i].speed.array[2] * planets[i].speed.array[2]);
	  sum_with_correction(energy, curr_energy, correction);
	}
	return energy / 2;
}

static real_type compute_p_energy(Planet *planets, int num_parts)
{
  real_type p_energy = 0.;
  real_type correction = 0.;
  for (int i = 0; i < num_parts; ++i)
  {
    for (int j = 0; j < num_parts; ++j)
    {
      if (i == j)
        continue;
      real_type dx = planets[j].pos.array[0] - planets[i].pos.array[0];
      real_type dy = planets[j].pos.array[1] - planets[i].pos.array[1];
      real_type dz = planets[j].pos.array[2] - planets[i].pos.array[2];

      real_type distanceSqr = dx * dx + dy * dy + dz * dz + softeningSquared;
      real_type distanceInv = 1.0 / sqrt(distanceSqr);
      real_type curr_energy = -G * planets[j].mass * distanceInv * planets[i].mass;
      sum_with_correction(p_energy, curr_energy, correction);
    }
  }
  return p_energy / 2;
}

static void compute_impulse(Planet *planets, int n, real_type sum_impulse[])
{
	real_type correction[] = {0, 0, 0};
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			real_type curr_impulse = planets[i].mass * planets[i].speed.array[j];
			sum_with_correction(sum_impulse[j], curr_impulse, correction[j]);
		}
	}
}

void Simulation::run(void) {
	log(__func__);

	real_type energy_k, energy_p;

	bodies = new Planet[count_planet];
	init_planet();

	energy_k = compute_k_energy(bodies, count_planet);
	energy_p = compute_p_energy(bodies, count_planet);
	real_type _energy = energy_k + energy_p;

	real_type impulse[] = {0, 0, 0};
	compute_impulse(bodies, count_planet, impulse);
	real_type _impulse = sqrt(pow(impulse[0], 2) + pow(impulse[1], 2) + pow(impulse[2], 2));



	std::cout << "Initial system energy k: " << energy_k << " p:" << energy_p << " Sum: " << _energy << " Impulse: " << _impulse << std::endl;

}
