#ifndef PID_H
#define PID_H

#include <vector>

class PID {
 public:


  // PID Coefficients
  double Kp;
  double Ki;
  double Kd;

  // PID Errors
  double p_error;
  double i_error;
  double d_error;

  // 
  double pre_cte;
  double sum_cte;
  
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void Init(double Kp, double Ki, double Kd);

  /**
   * Initialize Twiddle PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void TWR_Init(double Kp, double Ki, double Kd);

  /**
   * Assign run-a cte to previous cte
   * @param cte The current cross track error
   */
  void Update_PCte(double cte);

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte);

  /**
   * Calculate the total PID error.
   * @output The total PID error
   */
  double TotalError();

 private:
 
};

#endif  // PID_H