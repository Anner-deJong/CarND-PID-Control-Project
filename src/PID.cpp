#include "PID.h"
#include <iostream>


// Constructor
PID::PID(std::vector<double> params):
Kp(params[0]),
Ki(params[1]),
Kd(params[2]),
err_i(0),
init(false)
{}

// Destructor
PID::~PID() {}



double PID::getControl(double err) {
  if (!init) {
    err_prev = err;
    init = true;
  }

  // get difference (no timestep information available)
  err_d = (err - err_prev);  // / timestep
  err_i += err; // * timestep

  // calculate control variable
  control = -Kp * err -Kd * err_d -Ki * err_i;
  
  // update previous cte value      
  err_prev = err;

  return control;
}

