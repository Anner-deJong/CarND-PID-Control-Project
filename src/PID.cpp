#include "PID.h"
#include <iostream>


// Constructor
PID::PID(std::array<double, 3> gains):
Kp(gains[0]),
Ki(gains[1]),
Kd(gains[2]),
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

