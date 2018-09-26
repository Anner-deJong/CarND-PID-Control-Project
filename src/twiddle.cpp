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

// init function, not necessary, only if prior params are known
void TWIDDLE::init(std::vector<double> prior_params) {
  if (prior_params.size() != 3) {
    std::cout << "Unable to set params (size 3) to prior_params (size " << prior_params.size() << ")" << std::endl;
  }
  else {
    params = prior_params;
  }
}

std::vector<double> TWIDDLE::run() {

  best_err = 2;

  while (d_params[0] + d_params[1] + d_params[2] > tolerance) {
    for (int i=0; i<params.size(); ++i) {

      // increasing params[i]
      params[i] += d_params[i];
      cur_err = 2; //myFUNC(params);
      if (cur_err < best_err) {
        best_err = cur_err;
        d_params[i] *= 1.1;
      }

      else {
        // decreasing params[i]
        params[i] -= 2 * d_params[i];
        cur_err = 2; //myFUNC(params);
        if (cur_err < best_err) {
          best_err = cur_err;
          d_params[i] *= 1.1;
        }

        // neither, reset params[i] and decrease d_params[i]
        else {
          params[i] += d_params[i];
          d_params[i] *= 0.9;
        }
      }
    }
  }

  return params;
}

double TWIDDLE::dummy_cte_function(std::vector<double> params) {
  return 2;
}