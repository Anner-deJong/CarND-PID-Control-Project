#ifndef TWIDDLE_H
#define TWIDDLE_H

#include <vector>

class TWIDDLE {

public:

  // ctor + dtor
  TWIDDLE(double new_tolerance);
  virtual ~TWIDDLE();

  // member functions
  void init(std::vector<double> prior_params);
  std::vector<double> run();
  double dummy_cte_function(std::vector<double> params);

private:

  //member variables
  double tolerance;
  std::vector<double> params;
  std::vector<double> d_params;
  double best_err;
  double cur_err;

};


#endif