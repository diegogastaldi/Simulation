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
printLog("Inicializacion is complete \n");
}
double street::ta(double t) {
printLog("ta is initialized \n");
	return Sigma;
}

void street::dint(double t) {
printLog("dint is initialized \n");
	if (output && (amount_street >= 2)) {
		amount_street--;
		distance.pop_back();
		distance = update(distance, Sigma, output);
		Sigma = distance.back()/speed_cars;
	} else {
		if (output && ((amount_street == 0) || (amount_street == 1))) {
			amount_street = 0;
			distance.clear(); 
			Sigma = std::numeric_limits<double>::max();
		} else {
			if (!output) {
				distance = update(distance, Sigma, output);
				Sigma = std::numeric_limits<double>::max();
			} else {
				if (amount_street < 0) {	
					/*ERROR*/;
printLog("dint error \n");
				}
			}
		}
	}
printLog("dint is complete \n");
}

void street::dext(Event x, double t) {
printLog("dext is initialized %f \n", t);
	double *value;
	value = (double*)x.value;
printLog("dext is initialized %f \n", t);
printLog("dext: port %i \n", x.port);
printLog("dext: value %f \n", *value);

	if (x.port == 0) {
		if ((value[0] == 2) && (amount_street > 0))  {
			distance = update(distance, e, output);
			Sigma = Sigma - e;
		} else {
			if (amount_street == 0) {
				Sigma = std::numeric_limits<double>::max();
				output = value[0] == 2;
			} else {
				if ((value[0] != 2) && (amount_street > 0)) {
					distance = update(distance, e, output);
					Sigma = std::numeric_limits<double>::max();
					output = false;
				} else {
					/*ERROR*/
				}
			}
		}
	} else {
		if (x.port == 1) {
			if (amount_street == 0) {
				amount_street = 1;
				distance.clear();
				distance.push_front(size_street);
				Sigma = (size_street/speed_cars);
			} else {
				if ((amount_street >= 1) && (((amount_street + 1) * size_cars) <= size_street) && ((size_street - (update(distance, e, output)).front()) >= size_cars)) {
					amount_street++;
					distance = (update(distance, e, output));
					distance.push_front(size_street);
					Sigma = Sigma - e;
				} else {
					if ((amount_street + 1) * size_cars > size_street) {
						/*Error*/;
printLog("dext street error \n");
					} else {
						if (((amount_street + 1) * size_cars <= size_street) && (amount_street > 0) && (size_street - (update(distance, e, output)).front() < size_cars)) {
							distance = update(distance, e, output);
							Sigma = Sigma - e;
						} else {
							/*Error*/
						}
					}
				}
			}
		} else {
			/*port error*/
printLog("dext street port error \n");
		}
	}
printLog("dext is complete \n");
}

Event street::lambda(double t) {
printLog("lambda is initialized \n");
	return Event(&i,0);
}
void street::exit() {
printLog("exit: %f \n", amount_street);
}