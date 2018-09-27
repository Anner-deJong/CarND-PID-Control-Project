# **CarND Term 2 Project 4 Writeup** 
# **PID controller** 

#### This repository contains a c++ implementation of a PID controller. More specifically for this project, a PID controller class instance is used to control the steering angle for a car around a race track, and another instance is used to control its throttle (speed).

</br>


The repository is structured so that it works together with the [simulation environment provided by Udacity](https://github.com/udacity/self-driving-car-sim/releases). (The link between the environment and the code is via [uWebSocketIO](https://github.com/uNetworking/uWebSockets), and already provided by Udacity). Furthermore, this writeup does *not* include a full explanation about [PID controllers](https://en.wikipedia.org/wiki/PID_controller). It instead lists my overall approach of this project and my interpretation and choice of the various PID controller variables.

---

## Important scripts

This writeup will first give an overview of this repository's code by going through 3 .cpp files, and then describe how the PID control gains were chosen:

#### [1. PID.cpp](#1.-PID.cpp),
#### [2. twiddle.cpp](#2.-twiddle.cpp),
#### [3. main.cpp](#3.-main.cpp),
#### [4. Tweaking PID gains](#4.-Tweaking-PID-gains).


### 1. PID.cpp

The PID.cpp file takes care of implementing a straightforward PID controller.
It has 5 important member variables, namely the three gain parameters: proportional gain `Kp`, integral gain `Ki`, and derivate gain `Kd`, and also two parameters to keep track of the error integral and the derivative respectively: `err_i` and `err_prev`. Normally keeping track of these last two variables requires the specific time elapsed since the last timestep. Since this is not available, a constant time interval is assumed.

Calling the function with a new timestep's error will update the internal integral and derivative parameters, and return a control value calculated with `control = -Kp * err -Kd * err_d -Ki * err_i`. 

### 2. twiddle.cpp

The idea of the twiddle algorithm, as taught in class, is to automatically tune the control gains of a PID controller instance (or more generally any set of parameters for any function that has return some defined 'goodness' metric).

    void run(std::vector<double> &prior_params, double (*f)(const std::vector<double> &));

However, since no function returning the performance of a set of PID control parameters is available, this twiddle implementation is an idle class on side.

### 3. main.cpp

Most of main.cpp is already setup by Udacity, what is new is the creation of two PID controllers: `steer_pid` for controlling the steering angle and `throttle_pid` for controlling the throttle. The latter one adjusts the speed. For both these controllers, the control gains are manually tweaked and hardcoded inside main.cpp.

It also creates a twiddle instance and calls the `TWIDDLE::run(control_gain_params, error_function)` API on the `steer_pid` control gains. Since a dummy function is passed however, this call does not adjust the gains. <br>
If a proper error function was available, the twiddle API could also be called on the `throttle_pid` control gains to optimize those control variables as well. <br>
Since this would influence the performance of the `steer_pid` control gains, a slightly fancier version of twiddle would actually be nicer, one that can adjust all 6 control gains (of both the PID controllers) at the same time.

After having created the PID controller instances, the main script takes care of running the interaction with the simulator. At each simulator timestep, it will call each controller, and pass the control outputs back to the simulator.

#### Steering PID controller `steer_pid`



    double steer_control = steer_pid.getControl(cte);
    if (steer_control < -1) {steer_control = -1;}
    else if (steer_control > 1) {steer_control = 1;}
    
cte stands for cross track error, and is the lateral difference between the car's position and the middle of the road. The `steer_control` is then clipped in the range [-1., 1.] as the simulation environment does not use values outside this range. This is only for understanding of the control variable, as the simulation environment can take care of the clipping automatically.

#### Throttle PID controller `throttle_pid`

    double throttle_control = throttle_pid.getControl(cte*speed);
    throttle_control = std::max(-1., 1 - std::abs(throttle_control));
    
The throttle control is slightly different. It uses the same cte, but multiplies this with the speed. The line of reasoning behind this is that a certain cte with a higher speed is actually less stable than the same cte with a lower speed. Continuing this logic, the amount of speed correction (the control output) should be depedning on the actual speed. In other words, the car needs to push the breaks harder if it's getting out of bounds while driving with a higher speed.

Furthermore, the `throttle_control` does not directly influence the cte, and can hence not be directly used as actual throttle control command. Instead, and this is a somewhat freeform implementation of a PID controller, the absolute of the control value is taken, and subtracted from the maximum available throttle value 1. The resulting value is also clipped with a lower bound of -1, since also the throttle range is [-1., 1.]. The interpretation here is that the car should drive as fast as possible, mines a certain factor that grows with the cte * speed.



### 4. Tweaking PID gains

Since no error function is available for the twiddle implementation, all PID gains were tweaked manually:

|                | Kp (proportional gain) | Ki (integral gain) | Kd (derivative gain) |
| -------------- |:----------------------:|:------------------:|:--------------------:|
| `steer_pid`    | 0.5                    | 0                  | 15                   |
| `throttle_pid` | 0.05                   | 0                  | 0.5                  |

This is tedious and time consuming. As such, these values are probably far from optimal. They are sufficient to have the car drive around the track safely, but with better tweaking I expect it to be possible for the car to drive smoother and/or faster.

The Kp term, especially for the `steer_pid`, was quite sensitive. A value of >3 would make the car sway around quite dangerously. A value of 1.5 compared to .5 however did not make much difference. 
Considering the Ki's, it is interesting to note they are zero. It seems the car did not have a huge bias, and as such no integral gains were required. <br>
Especially the Kd terms provided important, to dampen the system and have the car smoothly return to the center of the road once astray. For the `steer_pid` controller the Kd term had to be sufficiently high, but afterwards did not seem to make much difference for the range [15., 23]. Higher values were not tried.

The conclusion here is that:
* the derivative gain is the most important, and needs to be at least a magnitude bigger than the Kp value
* compared among the two controllers, it seems the output for the throttle control simply needs to be smaller, and hence these gains are magnitude smaller than those for the steering controller. This makes some sense considering the throttle control is preferably in the range [0, 1.], whereas the steering control is in [-1., 1.].

## Note

Considering an error function calculating the 'goodness' of a certain set of gains for a PID controller, it is stated that one is not available. This is theoretically true, although the current environment does seem to allow for a hack up to implement one. A metric would have to be devised, but the main problem is actually running the simulator environment automatically. Right now, the simulator needs to be manually started in order to drive the car. How it is possible to do this automatically, and hence have an error function that is able to run the environment on its own, I do not know.



