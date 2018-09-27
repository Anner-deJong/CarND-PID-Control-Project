#include "twiddle.h"
#include <iostream>


// constructor
TWIDDLE::TWIDDLE(double new_tolerance) {
  tolerance = new_tolerance;
  params = {0, 0, 0};
  d_params = {1, 1, 1};
}

//destructor
TWIDDLE::~TWIDDLE() {}

// depreciated
// init function, not necessary, only if prior params are known
void TWIDDLE::init(std::vector<double> &prior_params) {
  if (prior_params.size() != 3) {
    std::cout << "Unable to set params (size 3) to prior_params (size " << prior_params.size() << ")" << std::endl;
  }
  else {
    params = prior_params;
  }
}

// main functionality
void TWIDDLE::run(std::vector<double> &prior_params, double (*err_func)(const std::vector<double> &)) {

  best_err = 2;

  while (d_params[0] + d_params[1] + d_params[2] > tolerance) {
    for (int i=0; i<prior_params.size(); ++i) {

      // increasing params[i]
      prior_params[i] += d_params[i];
      cur_err = err_func(prior_params);
      if (cur_err < best_err) {
        best_err = cur_err;
        d_params[i] *= 1.1;
      }

      else {
        // decreasing params[i]
        prior_params[i] -= 2 * d_params[i];
        cur_err = err_func(prior_params);
        if (cur_err < best_err) {
          best_err = cur_err;
          d_params[i] *= 1.1;
        }

        // neither, reset params[i] and decrease d_params[i]
        else {
          prior_params[i] += d_params[i];
          d_params[i] *= 0.9;
        }
      }
    }
  }
}

// templates
std::vector<double> TWIDDLE::run(double (*err_func)(const std::vector<double> &)) {
  TWIDDLE::run(params, err_func);
  return params;
}


double dummy_cte_function(const std::vector<double> &params) {
  return 1;
}