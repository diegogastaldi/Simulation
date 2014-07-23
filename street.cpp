#include "street.h"
void street::init(double t,...) {
	va_list parameters;
	va_start(parameters, t);

	size_cars = va_arg( parameters, double);
	speed_cars = va_arg( parameters, double);
	size_street = va_arg( parameters, double);

	/*zero -> false
	otherwise -> true*/

	output = (bool) va_arg( parameters, double);

	Sigma = std::numeric_limits<double>::max();
	amount_street = 0;

	i = 1;
}
double street::ta(double t) {
	return Sigma;
}

void street::dint(double t) {
	if (output && (amount_street >= 2)) {
		amount_street--;
		distance.pop_back();
		distance = update(distance, Sigma, output, t);
		Sigma = distance.back()/speed_cars;
	} else {
		if (output && ((amount_street == 0) || (amount_street == 1))) {
			amount_street = 0;
			distance.clear(); 
			Sigma = std::numeric_limits<double>::max();
		} else {
			if (!output) {
				distance = update(distance, Sigma, output, t);
				Sigma = std::numeric_limits<double>::max();
			} else {
				if (amount_street < 0) {	
					/*ERROR*/;
					printLog("Error: in method dint at street.cpp {a car must leave, but there is not a car on the street} TIME: %f\n", t);
					std::exit(EXIT_FAILURE);
				}
			}
		}
	}
}

void street::dext(Event x, double t) {
	double *value;
	value = (double*) x.value;

	if (x.port == 0) {
		if (amount_street == 0) {
			output = (value[0] == 2);
		} else {
			if (value[0] == 2)  {
				distance = update(distance, e, output, t);
				output = true;
				Sigma = distance.back() / speed_cars;
			} else {
				if (value[0] != 2) {
					distance = update(distance, e, output, t);
					output = false;
					Sigma = std::numeric_limits<double>::max();
				}
			}
		}
	} else {
		if (x.port == 1) {
			if (amount_street == 0) {
				amount_street = 1;
				distance.clear();
				distance.push_front(size_street);
				if (output)
					Sigma = (size_street/speed_cars);
			} else {
               	if ((amount_street + 1) * size_cars > size_street) {
					/*Error*/;
					printLog("Error: in method dext at street.cpp {a car must leave, but there is not place on the street} TIME: %f\n", t);
					std::exit(EXIT_FAILURE);
				}   
                else {
                    if ((amount_street >= 1) && (((amount_street + 1) * size_cars) <= size_street) && ((size_street - (update(distance, e, output, t)).front()) >= size_cars)) {
					    amount_street++;
    				    distance = (update(distance, e, output, t));
					    distance.push_front(size_street);
					    Sigma = Sigma - e;
				    } else {
						if (((amount_street + 1) * size_cars <= size_street) && (amount_street > 0) && (size_street - (update(distance, e, output, t)).front() < size_cars)) {
							distance = update(distance, e, output, t);
							Sigma = Sigma - e;
							printLog("Warning: Street {a car was ignored because there is not place}TIME: %f\n", t);
						}
					}
				}
			}
		}
	}
}

Event street::lambda(double t) {
	return Event(&i,0);
}
void street::exit() {
     printLog("exit: ont the street there is %f cars.\n", amount_street);
}
