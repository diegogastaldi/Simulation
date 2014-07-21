#include "street.h"
void street::init(double t,...) {
	va_list parameters;
	va_start(parameters, t);

	size_cars = va_arg( parameters, double);
	speed_cars = va_arg( parameters, double);
	size_street = va_arg( parameters, double);
	output = va_arg( parameters, double);

	Sigma=0;
	amount_street = 0;
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
	double i = 1;
	return Event(&i,0);
}
void street::exit() {

}

list <double> street::update(list <double> dist, double time, bool output) {
	/*new_list has "times" updated*/
	list <double> new_list;
	double new_time;
	for (int i = 0; i<dist.size(); i++) {
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
	}
	/*this list has not times equals*/
	list<double> list_not_enzimed;
	int first;
	for (int i = 0; i<new_list.size(); i++) {
		first = new_list.front();
		new_list = update_tail(new_list, first);
		list_not_enzimed.push_back(first);
	}
	
	return list_not_enzimed;
}

list <double> street::update_tail(list <double> dist, double first) {
	list<double> list_result;
	bool finished = false;
	double aux;
	for(int i = 0; i < dist.size(); (i++ && !finished)) {	
		aux = dist.front();
		if (aux <= first) {
			aux = aux + size_cars;
			list_result.push_back(aux);
		} else {
			finished = true;
		}
	}
	for(int i = 0; i < dist.size(); i++) {	
		aux = dist.front();	
		list_result.push_back(aux);
	}	
	return list_result;	
}