#include "PID.h"

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
  PID::Kp = Kp;
  PID::Ki = Ki;
  PID::Kd = Kd;
  
}

void PID::TWR_Init(double Kp, double Ki, double Kd)
{
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
  PID::Kp = Kp;
  PID::Ki = Ki;
  PID::Kd = Kd;

  p_error = 0;
  i_error = 0;
  d_error = 0;

  sum_cte = 0.0;

}

void PID::Update_PCte(double cte)
{
  /**
   * TODO: assign run-a cte to pre_cte.
   */

  pre_cte = cte;

}

void PID::UpdateError(double cte)
{
  /**
   * TODO: Update PID errors based on cte.
   */

  sum_cte += cte;

  p_error = Kp * cte;
  i_error = Ki * sum_cte;  
  d_error = Kd * (cte - pre_cte);

  pre_cte = cte;

}

double PID::TotalError()
{
  /**
   * TODO: Calculate and return the total error
   */
  return - (p_error+i_error+d_error);  // TODO: Add your total error calc here!
}


