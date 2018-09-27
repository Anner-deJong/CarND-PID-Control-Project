# **CarND Term 2 Project 4 Writeup** 
# **PID controller** 

#### This repository contains a c++ implementation of a PID controller. More specifically for this project, a PID controller class instance is used to control the steering angle for a car around a race track, and another instance is used to control its throttle (speed).

</br>


The repository is structured so that it works together with the [simulation environment provided by Udacity](https://github.com/udacity/self-driving-car-sim/releases). (The link between the environment and the code is via [uWebSocketIO](https://github.com/uNetworking/uWebSockets), and already provided by Udacity). Furthermore, this writeup does *not* include a full explanation about [PID controllers](https://en.wikipedia.org/wiki/PID_controller). It instead lists my overall approach of this project and my interpretation and choice of the various PID controller variables.

---

## Important scripts

This writeup will first give an overview of this repository's code by going through 3 .cpp files, and then describe how the PID control gains were chosen:

#### [1. PID.cpp](#1.-PID.cpp)
#### [2. twiddle.cpp](#2.-twiddle.cpp)
#### [3. main.cpp](#3.-main.cpp)
#### [4. Tweaking PID gains](#4.-Tweaking-PID-gains)


### 1. PID.cpp

The PID.cpp file takes care of implementing a straightforward PID controller.
It has 5 important member variables, namely the three gain parameters: proportional gain `Kp`, integral gain `Ki`, and derivate gain `Kd`, and also two parameters to keep track of the error integral and the derivative respectively: `err_i` and `err_prev`. Normally keeping track of these last two variables requires the specific time elapsed since the last timestep. Since this is not available, a constant time interval is assumed.

Calling the function with a new timestep's error will update the internal integral and derivative parameters, and return a control value calculated with `control = -Kp * err -Kd * err_d -Ki * err_i`. 

### 2. twiddle.cpp

    VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,const vector<VectorXd> &ground_truth)

### 3. main.cpp

Most of main.cpp is already setup by Udacity, what is new is the creation of two PID controllers: `steer_pid` for controlling the steering angle and `throttle_pid` for controlling the throttle. The latter one adjusts the speed. For both these controllers, the control gains are manually tweaked and hardcoded inside main.cpp.

It also creates a twiddle instance and calls the `TWIDDLE::run(control_gain_params, error_function)` API on the `steer_pid` control gains. Since a dummy function is passed however, this call does not adjust the gains. <br>
If a proper error function was available, the twiddle API could also be called on the `throttle_pid` control gains to optimize those control variables as well. <br>
Since this would influence the performance of the `steer_pid` control gains, a slightly fancier version of twiddle would actually be nicer, one that can adjust all 6 control gains (of both the PID controllers) at the same time.

#### Steering `PID controller`

After having created the PID controller instances, the main scripts calls

    double steer_control = steer_pid.getControl(cte);
    if (steer_control < -1) {steer_control = -1;}
    else if (steer_control > 1) {steer_control = 1;}
    
cte stands for cross track error, and is the lateral difference between the car's position and the middle of the road. The `steer_control` is then clipped in the range [-1, 1] as the simulation environment does not use values outside this range. This is only for understanding of the control variable, as the simulation environment can take care of the clipping automatically.

    double throttle_control = throttle_pid.getControl(cte*speed);
    throttle_control = 1 - std::abs(throttle_control);
    
The throttle control is slightly different. It uses the same cte, but multiplies this with the speed. The line of reasoning behind this is that the certain cte with a higher speed is actually less stable than the same cte with a lower speed. Continueing this logic, the amount of speed correction (the control output) should , In other words, the car needs to push the breaks harder if its getting out of bounds to the same extent but with a higher speed.

The main.cpp file takes care all of these calculations are 


they are used to calculate control values for each timestep in a continuous loop interacting with the simulation environment.

### 4. Tweaking PID gains

|                | Kp   | Ki   | Kd   |
| -------------- |:----:|:----:|:----:|
| `steer_pid`    | 0.5  | 0    | 15   |
| `throttle_pid` | 0.05 | 0    | 0.5  |

## Note

Considering an error function calculating the 'goodness' of a certain set of gains for a PID controller, some solutions with the current repository could actually be thought of.

FINISH FINISH




