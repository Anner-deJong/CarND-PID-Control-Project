#ifndef PID_H
#define PID_H

#include <vector>

class PID {

public:

// ctor + dtor
  PID(std::vector<double> params);
  virtual ~PID();

  // member functions
  double getControl(double cte);
  
private:

  // member variables
  bool init;
  double control;

  // controller coefficients
  const double Kp;
  const double Ki;
  const double Kd;

  // keeping track of various cte related properties
  double cte_prev;
  double cte_d;
  double cte_i;

};

#endif