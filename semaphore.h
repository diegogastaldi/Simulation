//CPP:sources/semaphore.cpp
#if !defined semaphore_h
#define semaphore_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"



class semaphore: public Simulator { 
double Sigma;
double color;

double t_red;
double t_green;
double t_yellow;

public:
	semaphore(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
