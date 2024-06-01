#ifndef PLANET_H
# define PLANET_H

# include <ctime>
# include <random>

typedef float real_type;

typedef union {
	struct {
		real_type x;
		real_type y;
		real_type z;
	};
	real_type array[3];
} vec3;

struct PlanetConfig {

	real_type mass_min, mass_max;

	PlanetConfig(void);
	virtual ~PlanetConfig(void);

	virtual void gen_position(vec3 *pos) const = 0;
	virtual void gen_speed(vec3 *speed) const = 0;
	virtual void gen_acceleration(vec3 *acc) const = 0;
	virtual void gen_mass(real_type *mass) const = 0;

};

struct CubePlanetConfig: public PlanetConfig {

	real_type len;

	CubePlanetConfig(void);

	virtual void gen_position(vec3 *pos) const override;
	virtual void gen_speed(vec3 *speed) const override;
	virtual void gen_acceleration(vec3 *acc) const override;
	virtual void gen_mass(real_type *mass) const override;

};

struct Planet {

	vec3 pos;
	vec3 speed;
	vec3 acceleration;
	real_type mass;

};

#endif
