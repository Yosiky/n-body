#ifndef SIMULATION_H
# define SIMULATION_H

# include <iostream>

class Simulation {

	int count_planet;
	int time_step;
	int sim_time;

	bool verbosity;

	void log(const char *str);

public:

	Simulation(int _count_planet, int _time_step, int _sim_time, bool _verbosity=false);

	void run(void);

};


#endif
