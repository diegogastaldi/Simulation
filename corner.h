//CPP:sources/corner.cpp
#if !defined corner_h
#define corner_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "cstdlib"
#include "iostream"
#include "list"
#include "limits"

class corner: public Simulator { 
	/*Parameters*/
	double size_cars;
	double speed_cars;
	double size_corner;
	double out_percent0;
	double out_percent1;
	
	/*Atributes*/
	double a_cars;
	std::list<double> dist;
	double sigma;




public:
	corner(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
private: 
	std::list<double> update_list(std::list<double> dist, double time);
};
#endif
