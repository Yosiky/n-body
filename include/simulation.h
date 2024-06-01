#ifndef SIMULATION_H
# define SIMULATION_H

# include <iostream>
# include <cmath>
# include "planet.h"

class Simulation {

	Planet *bodies;
	PlanetConfig *planet_config;

	int count_planet;
	int iter_count;
	int sim_time;
	real_type time_step;

	bool verbosity;

	void log(const char *str) const;
	void log_error(const char *str) const;
	void calc_time_step(void);
	void init_planet(void);

public:

	Simulation(int _count_planet, int _iter_count, int _sim_time, PlanetConfig *planet_config, bool _verbosity=false);

	void run(void);

};


#endif
