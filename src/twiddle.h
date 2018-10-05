#ifndef TWIDDLE_H
#define TWIDDLE_H

#include <vector>
#include <array>
#include <functional>

class TWIDDLE {

public:

  // ctor + dtor
  TWIDDLE(double new_tolerance);
  virtual ~TWIDDLE();

  // member functions
  void init(std::array<double, 3> &prior_params);
  // void run(std::array<double, 3> &prior_params, double (*err_func)(const std::array<double, 3> &));
  void run(std::array<double, 3> &prior_params, std::function<double(const std::array<double, 3> &)> err_func);
  std::array<double, 3> run(double (*f)(const std::array<double, 3> &));
  

private:

  //member variables
  double tolerance;
  std::array<double, 3> params;
  std::array<double, 3> d_params;
  double best_err;
  double cur_err;

};

#endif