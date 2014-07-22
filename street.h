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
			new_time = dist.front() - time;

			if (new_time >= 0) {
				new_list.push_back(new_time);
			} else {
				if (!output)
					new_list.push_back(0);
				else {
					/*ERROR*/
				}
			}
			dist.pop_front();
		}

		/*this list has not times equals*/
		std::list<double> list_not_enzimed;
		int first;

		while (!new_list.empty()) {
			first = new_list.front();
			new_list = update_tail(new_list, first);
			list_not_enzimed.push_back(first);

			new_list.pop_front();
		}
	
		return list_not_enzimed;
	}

	std::list <double> update_tail(std::list <double> dist, double first) {
		std::list<double> list_result;
		bool finished = false;
		double aux;

		while (!dist.empty() && !finished) {
			aux = dist.front();
			if (aux <= first) {
				aux = aux + size_cars;
				list_result.push_back(aux);
			} else {
				finished = true;
			}
			dist.pop_front();
		}	

		while (!dist.empty()) {
			aux = dist.front();	
			list_result.push_back(aux);
			dist.pop_front();
		}	
		return list_result;	
	}
};
#endif
