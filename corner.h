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
	double corner_number;
	/*Atributes*/
	double a_cars;
	std::list<double> dist;
	double sigma;
    double i;



public:
	corner(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
private: 
	std::list<double> update_list(std::list<double> dist, double time, double time_simulation) {
		/*new_list has "times" updated*/
		std::list<double> new_list;
		double new_time;

		while (!dist.empty()) {
			new_time = dist.back() - (time * speed_cars);

			if (new_time >= 0) {
				new_list.push_front(new_time);
			} else {
				/*ERROR*/
				printLog("Error: in method update_list at corner.h (corner %f){a car must leave the street, but was not called the function dint} TIME: &f\n", corner_number, time_simulation);
				std::exit(EXIT_FAILURE);
			}
			dist.pop_back();
		}
		return new_list;
	}	
};
#endif
