#include "car_generator.h"
void car_generator::init(double t,...) {
    //The 'parameters' variable contains the parameters transferred from the editor.
    va_list parameters;
    va_start(parameters,t);

    /* This is the parameter of the exponential distribution*/
    parameter_distribution=va_arg(parameters, double);
    
    /*At time Zero, the generator sends a car*/
    sigma = 0;

    /*Output*/
    i = 1;
    
	/*Initialize seed*/
	srand(time(NULL));
}
double car_generator::ta(double t) {
    return sigma;
}
void car_generator::dint(double t) {
    //Generate a random number between 0 and 1.
    float r;
    r = (float)rand()/(float)(RAND_MAX+1);
           
    //Put it as a parameter to the inverse distribution function.
    sigma = (double)-parameter_distribution*log(r);
    /*    printLog("%f\n", sigma);*/
    /*sigma = parameter_distribution;*/
}
void car_generator::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition

/* This module receives no extern events*/
}
Event car_generator::lambda(double t) {
/*Always sends one*/
return Event(&i,0);
}
void car_generator::exit() {
//Code executed at the end of the simulation.

}
