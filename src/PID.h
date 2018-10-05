#ifndef PID_H
#define PID_H

#include <vector>
#include <array>

class PID {

public:

// ctor + dtor
  PID(std::array<double, 3> gains);
  virtual ~PID();

  // member functions
  double getControl(double err);
  
private:

  // member variables
  bool init;
  double control;

  // controller gains
  const double Kp;
  const double Ki;
  const double Kd;

  // keeping track of various cte related properties
  double err_prev;
  double err_d;
  double err_i;

};

#endif