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
		distance.pop_front();
		distance = update(distance, Sigma, output);
		Sigma = distance.front()/speed_cars;
	} else {
		if (output && (amount_street == 1)) {
			amount_street = 0;
			distance.clear(); 
			Sigma = std::numeric_limits<double>::max();
		} else {
			if ((!output) || (amount_street <= 0)) {
				/*ERROR*/;
			}
		}
	}
}

void street::dext(Event x, double t) {
	int *port = (int*)x.port;
	double *value = (double*)x.value;

	if ((port[0] == 1) && (value[0] == 2) && (amount_street > 0))  {
		distance = update(distance, e, output);
		Sigma = Sigma - e;
	} else {
		if ((port[0] == 1) && (amount_street == 0)) {
			Sigma = std::numeric_limits<double>::max();
			output = value[0] == 2;
		} else {
			if ((port[0] == 1) && (value[0] != 2) && (amount_street > 0)) {
				distance = update(distance, e, output);
				Sigma = std::numeric_limits<double>::max();
				output = false;
			} else {
				if ((port[0] == 0) && (amount_street >= 1) && (((amount_street + 1) * size_cars) <= size_street) && ((size_street - (update(distance, e, output)).back()) >= size_cars)) {
					amount_street++;
					distance = (update(distance, e, output));
					distance.push_front(size_street);
					Sigma = Sigma - e;
				} else {
					if ((port[0] == 0) && ((amount_street + 1) * size_cars > size_street)) {
						/*Error*/;
					} else {
						if ((port[0] == 0) && ((amount_street + 1) * size_cars <= size_street) && (amount_street > 0) && (size_street - (update(distance, e, output)).back() < size_cars)) {
							distance = update(distance, e, output);
							Sigma = Sigma - e;
						} else {
							if ((port[0] == 0) && (amount_street == 0)) {
								amount_street = 1;
								distance.clear();
								distance.push_front(size_street);
								Sigma = (size_street/speed_cars);
							}
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

}