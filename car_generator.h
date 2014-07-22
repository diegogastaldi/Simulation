//CPP:sources/car_generator.cpp
#if !defined car_generator_h
#define car_generator_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"



class car_generator: public Simulator { 
// Declare the state,
// output variables
// and parameters
double parameter_distribution;
double sigma;

double i;
















public:
	car_generator(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
