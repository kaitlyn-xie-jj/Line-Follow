#ifndef _MOTOR_h
#define _MOTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

//LeftBack = M1; LeftFront = M2; RightBack = M3; RightFront = M4;
const int c_i_PIN_WHEEL_LEFTFRONT_PWM1 = 41;
const int c_i_PIN_WHEEL_LEFTFRONT_PWM2 = 42;
const int c_i_PIN_WHEEL_LEFTBACK_PWM1 = 39;
const int c_i_PIN_WHEEL_LEFTBACK_PWM2 = 40;
const int c_i_PIN_WHEEL_RIGHTFRONT_PWM1 = 47;
const int c_i_PIN_WHEEL_RIGHTFRONT_PWM2 = 48;
const int c_i_PIN_WHEEL_RIGHTBACK_PWM1 = 45;
const int c_i_PIN_WHEEL_RIGHTBACK_PWM2 = 46;
//Lift(N20 * 2) = Entended MotorDiver;  
const int c_i_PIN_LIFT_PWM1 = 11;
const int c_i_PIN_LIFT_PWM2 = 12;

const int c_i_PWM_WHEEL_FREQ = 20000;
const int c_i_PWM_WHEEL_RESOLUTION = 9;
const int c_i_PWM_LIFT_FREQ = 2000;
const int c_i_PWM_LIFT_RESOLUTION = 8;

const int c_i_PWMCH_WHEELLEFT1 = 0;
const int c_i_PWMCH_WHEELLEFT2 = 1;
const int c_i_PWMCH_WHEELRIGHT1 = 2;
const int c_i_PWMCH_WHEELRIGHT2 = 3;
const int c_i_PWMCH_LIFT1 = 4;
const int c_i_PWMCH_LIFT2 = 5;

void Set_MotorsDir(int smd_i_wlf, int smd_i_wlb, int smd_i_wrf, int smd_i_wrb, int smd_i_lift);
void Set_LiftSpeed(int sls_i_speed);
void Set_LiftMoveTime(long slmt_l_m2l, long slmt_l_m2h);
void InitMotor();
void MotorRun(int mr_i_leftSpeed, int mr_i_rightSpeed);
void LiftRun(int lr_i_speed);
void LiftToPositon(int ltp_i_pos);

#endif