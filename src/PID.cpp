#include "PID.h"
#include <iostream>


// Constructor
PID::PID(std::vector<double> params):
Kp(params[0]),
Ki(params[1]),
Kd(params[2]),
cte_i(0),
init(false)
{}

// Destructor
PID::~PID() {}



double PID::getControl(double cte) {
  if (!init) {
    cte_prev = cte;
    init = true;
  }

  // get difference 
  cte_d = (cte - cte_prev);  // timestep
  cte_i += cte; // * timestep

  // calculate control variable
  control = -Kp * cte -Kd * cte_d -Ki * cte_i;
  
  // update previous cte value      
  cte_prev = cte;

  return control;
}

