#include <iostream>
#include "simulation.h"

int main(int argc, char **argv) {
	int count_planet = 1;
	int time_step = 1;
	int sim_time = 1;

	switch (argc) {
	case 3:
		sim_time = std::atoi(argv[--argc]);
	case 2:
		time_step = std::atoi(argv[--argc]);
		count_planet = std::atoi(argv[--argc]);
		break ;
	default:
		std::cerr << "You are running a program with default values." << std::endl;
	}

	std::cout << "Your arguments is:" << std::endl;
	std::cout << "\tCount planet = " << count_planet << std::endl;
	std::cout << "\tTime step = " << time_step << std::endl;
	std::cout << "\tSimulation time = " << sim_time << std::endl;

	CubePlanetConfig planet_config;
	Simulation sim(count_planet, time_step, sim_time, &planet_config, true);

	sim.run();
	return (0);
}
