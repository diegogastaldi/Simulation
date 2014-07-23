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

double amount_street;          // amount the cars in the street
std::list <double> distance;   // distance from each car to next corner
double Sigma;
bool output;                   // indicates if the cars can out to the street

double i;                      // contains the value of out









public:
	street(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
private:
    /* This method updates the list according to the time that passed and if the cars can out*/             
	std::list <double> update(std::list <double> dist, double time, bool output, double time_simulation) {
		/*new_list has "times" updated*/
		std::list <double> new_list;
		double new_time;
        bool crowding = false;
        
		while (!dist.empty()) {
            /* updates time */  
			new_time = dist.back() - (time * speed_cars);

			if (new_time >= 0) {
				new_list.push_front(new_time);
			} else {
				if (!output) {
                    /*"stops"*/
					new_list.push_front(0);
					crowding = true;
				} else {
					/*ERROR*/
					printLog("Error: in method update at street.h {a car must leave the street, but was not called the function dint} TIME %f\n", time_simulation);
					std::exit(EXIT_FAILURE);
				}
			}
			dist.pop_back();
		}
        if (crowding)
        	new_list = update_tail(new_list);
	
		return new_list;
	}
    /* This method change the distances of the cars if the top two are the same*/
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
                /* Concatenate to the biginning*/
				list_result = push_all_front(update_tail(dist), list_result);
			} else {
                   list_result = push_all_front(dist, list_result);
            }
			return list_result;	
		} else {
			return dist;
		}

	}
    /* this method Concatenate the lists to the biginning*/
	std::list <double> push_all_front(std::list <double> list_up, std::list <double> list_res) {
        while (!list_up.empty()) {
            list_res.push_front(list_up.back());
            list_up.pop_back();
        }
        return list_res;
    }
};
#endif
