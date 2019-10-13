#include <math.h>
#include <uWS/uWS.h>
#include <iostream>
#include <string>
#include "json.hpp"
#include "PID.h"

// for convenience
using nlohmann::json;
using std::string;

// For converting back and forth between radians and degrees.
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
string hasData(string s) {
  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_last_of("]");
  if (found_null != string::npos) {
    return "";
  }
  else if (b1 != string::npos && b2 != string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  }
  return "";
}

int main() {
  uWS::Hub h;

  PID s_pid; // steer pid
  PID t_pid; // throttle/vehicle speed pid

  /**
   * TODO: Initialize the pid variable.
   */
  // 
  // s_pid.Init(0.25, 0.000025, 8); // p:0.25, i:2.5*1e-5, d:8 are good initial guess
  s_pid.Init(0.2, 0.001, 3);

  h.onMessage([&s_pid, &t_pid](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, 
                     uWS::OpCode opCode) 
  {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event
    if (length && length > 2 && data[0] == '4' && data[1] == '2') 
    {
      auto s = hasData(string(data).substr(0, length));

      if (s != "")
      {
        auto j = json::parse(s);

        string event = j[0].get<string>();

        if (event == "telemetry")
        {
          // j[1] is the data JSON object
          double cte = std::stod(j[1]["cte"].get<string>());
          double speed = std::stod(j[1]["speed"].get<string>());
          double angle = std::stod(j[1]["steering_angle"].get<string>());

          /**
           * TODO: Calculate steering value here, remember the steering value is
           *   [-1, 1].
           * NOTE: Feel free to play around with the throttle and speed.
           *   Maybe use another PID controller to control the speed!
           */
          json msgJson;

          // update error and calculate steer_value at each step
          s_pid.UpdateError(cte);
          double steer_value = s_pid.TotalError();
		      // limit steer value [-1,1]
  		    if (steer_value > 1.0) {steer_value = 1;}
  		    if (steer_value < -1.0){steer_value = -1;} 
  		    msgJson["steering_angle"] = steer_value;

          /*
          // throttle traget speed pid
          double target_speed = 30;
          t_pid.UpdateError(speed - target_speed);
          double throttle = t_pid.TotalError();
          // limit throttle value [0`,1]
          if(throttle > 0.3){throttle = 0.3;}
          if(throttle < -1E-5){throttle = 0.0;}
          msgJson["throttle"] = throttle;
          */
          
          // throttle, fixed value
          // msgJson["throttle"] = 0.35;

          // throttle as a function of steeriing angle
          double nsv = 1 - std::abs(steer_value);
          msgJson["throttle"] = nsv * nsv * 0.1 + nsv * 0.25; // throttle function of steer value, non-linear: smooth ride & 30-35 mph
          // msgJson["throttle"] = nsv * nsv * 0.15 + nsv * 0.25; // throttle function of steer value, non-linear: smooth ride & 40 mph
          // msgJson["throttle"] = nsv * nsv * nsv * 0.15 + nsv * nsv * 0.2 + nsv * 0.25; // throttle function of steer value, non-linear: 50 mph

          // print/debug
          std::cout << "CTE: " << cte << " Steering Value: " << steer_value << " Speed: " << speed << std::endl;          

          auto msg = "42[\"steer\"," + msgJson.dump() + "]";
          std::cout << msg << std::endl;
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
        }  // end "telemetry" if
      }

      else
      {
        // Manual driving
        string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }  // end websocket message if
  }
  ); // end h.onMessage

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    std::cout << "Connected!!!" << std::endl;
  });

  h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, 
                         char *message, size_t length) {
    ws.close();
    std::cout << "Disconnected" << std::endl;
  });

  int port = 4567;
  if (h.listen(port)) {
    std::cout << "Listening to port " << port << std::endl;
  } else {
    std::cerr << "Failed to listen to port" << std::endl;
    return -1;
  }
  
  h.run();
}