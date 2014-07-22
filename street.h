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

double i;









public:
	street(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
private:
	std::list <double> update(std::list <double> dist, double time, bool output) {
		/*new_list has "times" updated*/
		std::list <double> new_list;
		double new_time;

		while (!dist.empty()) {
			new_time = dist.back() - (time * speed_cars);

			if (new_time >= 0) {
				new_list.push_front(new_time);
			} else {
				if (!output)
					new_list.push_front(0);
				else {
					/*ERROR*/
					printLog("Error: in method update at street.h {a car must leave the street, but was not called the function dint}\n");
					std::exit(EXIT_FAILURE);
				}
			}
			dist.pop_back();
		}

		new_list = update_tail(new_list);
	
		return new_list;
	}

	std::list <double> update_tail(std::list <double> dist) {
		std::list<double> list_result;
		double first;
		double second;

		if (dist.size() >= 2) {
			first = dist.back();
			list_result.push_front(first);
			dist.pop_back();
			
			second = dist.back();
			if (first >= second) {
				second = first + size_cars;
				dist.pop_back();
				dist.push_back(second);

				list_result = update_tail(dist);
			} 
			return list_result;	
		} else {
			return dist;
		}

	}
};
#endif
