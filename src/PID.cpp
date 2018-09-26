#include "PID.h"
#include <iostream>


// Constructor
PID::PID(double Kp, double Ki, double Kd):
Kp(Kp),
Ki(Ki),
Kd(Kd),
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

