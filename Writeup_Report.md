# **Self-Driving Car Engineer**
# **Project: PID Controller**

## MK

Overview
---
Implement a PID controller in C++ to maneuver the vehicle/car around a race track. The car and race track simulator provides cross-track-error (CTE) and velocity (mph) to compute steering angle correction. Corrected steering angle maintains the car stay inside of the track lane.

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

#### Sensing (Telemetry)
Gather below listed data from simulator [Link](./src/main.cpp#L80-L102):
* Ego car localization data
* Previous unused path from the simulator
* Localization data of other cars

#### Prediction [Link](./src/main.cpp#L110-L165):
* Based on data from sensing predict other cars localization with respect to ego car. Detect whether other cars are present ahead, left, right of ego car

#### Next Steps and Future Updates
* Auto-tune PID parameters using algorithms such as Coordinate Ascent (Twiddle) or Stochastic Gradient Descent to further maximize vehicle speed

