#include "car_generator.h"
void car_generator::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);

parameter_distribution=va_arg(parameters, double);
sigma = 0;

i = 1;
}
double car_generator::ta(double t) {
//This function returns a double.
return sigma;
}
void car_generator::dint(double t) {
/*sigma = std::exponential_distribution rng (1/time_between_cars);*/
sigma = parameter_distribution;
}
void car_generator::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition

}
Event car_generator::lambda(double t) {
return Event(&i,0);
}
void car_generator::exit() {
//Code executed at the end of the simulation.

}
