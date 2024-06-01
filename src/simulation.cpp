#include "simulation.h"

void Simulation::log(const char *str) {
	if (verbosity)
		std::cout << str << std::endl;
}

Simulation::Simulation(int _count_planet, int _time_step, int _sim_time, bool _verbosity)
	:	count_planet(_count_planet),
		time_step(_time_step),
		sim_time(_sim_time), 
		verbosity(_verbosity) {

	Simulation::log(__func__);
}

void Simulation::run(void) {
	Simulation::log(__func__);


}
