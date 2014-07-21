//CPP:sources/street.cpp
#if !defined street_h
#define street_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "cstdlib"
#include "iostream"
#include "list"
#include "limits"

class street: public Simulator { 
double size_cars;
double speed_cars;
double size_street;

double amount_street;
std::list <double> distance;
double Sigma;
bool output;











public:
	street(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
private:
	std::list <double> update(std::list <double> dist, double time, bool output);
	std::list <double> update_tail(std::list <double> dist, double first);
};
#endif
