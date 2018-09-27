#ifndef TWIDDLE_H
#define TWIDDLE_H

#include <vector>

class TWIDDLE {

public:

  // ctor + dtor
  TWIDDLE(double new_tolerance);
  virtual ~TWIDDLE();

  // member functions
  void init(std::vector<double> &prior_params);
  void run(std::vector<double> &prior_params, double (*f)(const std::vector<double> &));
  std::vector<double> run(double (*f)(const std::vector<double> &));
  

private:

  //member variables
  double tolerance;
  std::vector<double> params;
  std::vector<double> d_params;
  double best_err;
  double cur_err;

};


double dummy_cte_function(const std::vector<double> &params);


#endif