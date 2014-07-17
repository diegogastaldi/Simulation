#include "semaphore.h"
void semaphore::init(double t,...) {
va_list parameters;
va_start(parameters, t);

t_red=va_arg( parameters, double);
t_green=va_arg( parameters, double);
t_yellow=va_arg( parameters, double);

color = va_arg( parameters, double);

if (color == 0) {
	Sigma = t_red;
} else if (color == 1) {
	Sigma = t_yellow;
} else if (color == 2) {
	Sigma = t_green;
}
}
double semaphore::ta(double t) {
return Sigma;
}
void semaphore::dint(double t) {
if (color == 0) {
	Sigma = t_green;
	color = 2;
} else if (color == 1) {
	Sigma = t_red;
	color = 0;
} else if (color == 2) {
	Sigma = t_yellow;
	color = 1;
}
}
void semaphore::dext(Event x, double t) {

}
Event semaphore::lambda(double t) {
return Event(&color,0);
}
void semaphore::exit() {

}
