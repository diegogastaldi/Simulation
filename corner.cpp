#include "corner.h"
void corner::init(double t,...) {
	va_list parameters;
	va_start(parameters, t);

	size_cars = va_arg( parameters, double);
	speed_cars = va_arg( parameters, double);
	size_corner = va_arg( parameters, double);
	out_percent0 = va_arg( parameters, double);

	sigma=0;
	a_cars = 0;
	/*Initialize seed*/
	srand(time(NULL));
}
double corner::ta(double t) {
	return sigma;
}

void corner::dint(double t) {
	if (a_cars >= 2) {
		a_cars--;
		dist.pop_front();
		dist = update_list(dist, sigma);
		sigma = dist.front()/speed_cars;
	} else {
		if (a_cars == 1) {
			a_cars = 0;
			dist.clear(); 
			sigma = std::numeric_limits<double>::max();
		} else {
			if (a_cars <= 0) {
				/*ERROR*/;
			}
		}
	}
}

void corner::dext(Event x, double t) {
	if ((a_cars >= 1) && (((a_cars + 1) * size_cars) <= size_corner) && ((size_corner - (update_list(dist, e)).back()) >= size_cars)) {
		a_cars++;
		dist = (update_list(dist, e));
		dist.push_back(size_corner);
		sigma = sigma - e;
	} else {
		if (((a_cars + 1) * size_cars > size_corner)) {
			/*Error*/;
		} else {
			if ((a_cars > 0) && (size_corner - dist.front() < size_cars)) {
				dist = update_list(dist, e);
				sigma = sigma - e;
			} else {
				if (a_cars == 0) {
					a_cars = 1;
					dist.clear();
					dist.push_front(size_corner);
					sigma = (size_corner/speed_cars);
				}
			}
		}
	}
}

Event corner::lambda(double t) {
	double num_rand = rand() % 101;
	double i = 1;
	
	if (num_rand <= out_percent0) {
		return Event(&i,0);
	} else {
		return Event(&i,1);
	}
}
void corner::exit() {

}
