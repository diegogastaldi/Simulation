#include "corner.h"
void corner::init(double t,...) {
	va_list parameters;
	va_start(parameters, t);

	size_cars = va_arg( parameters, double);
	speed_cars = va_arg( parameters, double);
	size_corner = va_arg( parameters, double);
	out_percent0 = va_arg( parameters, double);

	sigma = std::numeric_limits<double>::max();
	a_cars = 0;
	
	i = 1;
	/*Initialize seed*/
	srand(time(NULL));
}
double corner::ta(double t) {
	return sigma;
}

void corner::dint(double t) {
	if (a_cars >= 2) {
		a_cars--;
		dist.pop_back();
		dist = update_list(dist, sigma);
		sigma = dist.back()/speed_cars;
	} else {
		if ((a_cars == 1) || (a_cars == 0)) {
			a_cars = 0;
			dist.clear(); 
			sigma = std::numeric_limits<double>::max();
		} else {
			if (a_cars < 0) {
				/*ERROR*/;
				printLog("Error: in method dint at corner.cpp {a car must leave, but there is not a car on the corner}\n");
 				std::exit(EXIT_FAILURE);
			}
		}
	}
}

void corner::dext(Event x, double t) {
	if (a_cars == 0) {
		a_cars = 1;
		dist.clear();
		dist.push_front(size_corner);
		sigma = (size_corner/speed_cars);
	} else {
		if (((a_cars + 1) * size_cars > size_corner)) {
    		/*Error*/;
			printLog("Error: in method dext at corner.cpp {a car must leave, but there is not place on the corner}\n");
			std::exit(EXIT_FAILURE);
		} else {
            if ((a_cars >= 1) && (((a_cars + 1) * size_cars) <= size_corner) && ((size_corner - (update_list(dist, e)).front()) >= size_cars)) {
	         	a_cars++;
              	dist = (update_list(dist, e));
               	dist.push_front(size_corner);
               	sigma = sigma - e;
            } else {
                if (((a_cars + 1) * size_cars <= size_corner) && (a_cars > 0) && (size_corner - update_list(dist, e).front() < size_cars)) {
				    dist = update_list(dist, e);
				    sigma = sigma - e;
        			printLog("Warning: {a car was ignored because there is not place}\n");
			    }
			}
		}
	}
}

Event corner::lambda(double t) {
	double num_rand = rand() % 101;
	
	if (num_rand <= out_percent0) {
		return Event(&i,0);
	} else {
		return Event(&i,1);
	}
}
void corner::exit() {
     printLog("exit: on the corner there is %f cars.\n", a_cars);
}
