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
  - Integral Error: Ki * SUM(CTE); Ki: Integral gain constant and SUM(CTE): Summation of all CTEs from time(t) = 0 to current t
  - Differential/Derivative Error (Difference in CTEs between successive time steps) = Kd * (CTE - Previous-CTE); Kd:  Differential gain constant
* Calculate total-error/correction, which is the sum of Proportional, Integral, and Differential errors
* Apply total-error/correction as a steering angle adjustment to move the vehicle within lane boundaries
  
#### 3. PID Control

PID-controller (PID) is a feedback-loop control mechanism. PID continuously predicts the current error estimate: difference between the set-point/reference and measured/sensed variables. Based on the current error estimate it applies a correction (total error) based on proportional, integral, and derivative terms.


Proportional term is a correction term corresponding to current error estimate: difference between reference and sensed variables. 

Integral term is a correction term associated with the total accumulated error through all the previous time steps. Integral term can also be used as a correction factor for inherent bias error within the system.

Derivative term is a correction term associated with the current rate of change in error or the sensed variable itself. A control effect to minimize future trend of (Reference-Measured) estimate.

It is not necessary to apply PID control to all systems. Some of the systems can be controlled by just P-controller or PD-controller or PI controller depending on the system behavior.

Applying just P-controller can result in measured/sensed variable overshoot or undershoot the reference variable and consequently resulting in an oscillatory behavior. The D-controller term helps mitigate this effect by appropriate correction for the rate change of error. Below image shows the effect of just using P-controller versus PD-controller.

Although,the D-controller might mitigate or minimize the oscillatory behavior of the measured/sensed variable there might be a systemic bias error or residual error that might continue to persist. I-controller term is a correction term associated with minimizing or eliminating the residual error resulting from the inherent system bias or time history.

#### Next Steps and Future Updates
* Auto-tune PID parameters using algorithms such as Coordinate Ascent (Twiddle) or Stochastic Gradient Descent to further maximize vehicle speed

