# **Self-Driving Car Engineer**
# **Project: PID Controller**

## MK

Overview
---
Implement a Proportional-Integral-Derivative (PID) controller in C++ to maneuver the vehicle/car around a race track. The car and race track simulator provides cross-track-error (CTE) and velocity (mph) to compute steering angle correction. Corrected steering angle maintains the car stay inside of the track lane.

The Project
---
The goals/steps for this project:
* Build a PID controller and tune the PID hyperparameters
* Test the tuned PID controller on the vehicle/race-track simulator
* Vehicle must successfully drive a lap around the track
* There is no minimum vehicle speed criteria. However, maximize vehicle speed by tuning the PID parameters


[//]: # (Image References)

[image1]: ./Writeup_IV/HDPP_FRS.png "HDPP_FRS"

---
### Files Submitted

#### 1. Files included with submission to run the simulator in autonomous mode

Project includes the following files:
* main.cpp contains all the relevant code to fine tune the PID paramerters and to control the vehicle inside the simulator
* Writeup_Report.md summarizes the results
* The first attempt resulted in a distance of 38.9 miles without incident. Final output video [Link](https://www.youtube.com/watch?v=G4B1sXR3a6I&t=10s)
![][image1]


#### 2. Project code (main.cpp)

The main.cpp file contains code for the following set of tasks:
* Connect to race-track simulator using [micro-websocket](https://github.com/uNetworking/uWebSockets). Websocket handles two-way data transfer between planner and simulator
* Gather current vehicle parameters from simulator [Link](./src/main.cpp#L?-L?):
  - Cross track error (CTE)
  - Speed
  - Steering angle
* Calculate proprortional, integral, and derivative errors as follows:
  - Proportional Error: Kp * CTE; Kp: Proprotional gain constant
  - Integral Error: Ki * \int\limits_a^b; Kp: Integral gain constanti_error = Ki * sum_cte;  
  d_error = Kd * (cte - pre_cte);
  

#### Next Steps and Future Updates
* Auto-tune PID parameters using algorithms such as Coordinate Ascent (Twiddle) or Stochastic Gradient Descent to further maximize vehicle speed

