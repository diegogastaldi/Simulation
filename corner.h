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
	std::list<double> update_list(std::list<double> dist, double time) {
		/*new_list has "times" updated*/
		std::list<double> new_list;
		double new_time;
		for (double i = 0; i<dist.size(); i++) {
			new_time = dist.front() - time;

			if (new_time >= 0) {
				new_list.push_back(new_time);
			} else {
				/*ERROR*/
			}
		}
		return new_list;
	}	
};
#endif
