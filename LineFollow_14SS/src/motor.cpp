#include "motor.h"

static long g_l_LiftMoveTime_Mid2Low = 0;
static long g_l_LiftMoveTime_Mid2High = 0;
static int g_i_LiftCurrentPosition = 0, g_i_LiftSpeed = 0;
static int g_i_WheelDir_LeftFront = 1, g_i_WheelDir_LeftBack = 1, g_i_WheelDir_RightFront = 1, g_i_WheelDir_RightBack = 1;
static int g_i_LiftDir = 1;

void Set_MotorsDir(int smd_i_wlf, int smd_i_wlb, int smd_i_wrf, int smd_i_wrb, int smd_i_lift) {
    g_i_WheelDir_LeftFront = smd_i_wlf;
    g_i_WheelDir_LeftBack = smd_i_wlb;
    g_i_WheelDir_RightFront = smd_i_wrf;
    g_i_WheelDir_RightBack = smd_i_wrb;
    g_i_LiftDir = smd_i_lift;
}

void Set_LiftSpeed(int sls_i_speed) {
    g_i_LiftSpeed = sls_i_speed;
}

void Set_LiftMoveTime(long slmt_l_m2l, long slmt_l_m2h) {
    g_l_LiftMoveTime_Mid2Low = slmt_l_m2l;
    g_l_LiftMoveTime_Mid2High = slmt_l_m2h;
}

void InitMotor() {
    ledcSetup(c_i_PWMCH_WHEELLEFT1, c_i_PWM_WHEEL_FREQ, c_i_PWM_WHEEL_RESOLUTION);
    ledcSetup(c_i_PWMCH_WHEELLEFT2, c_i_PWM_WHEEL_FREQ, c_i_PWM_WHEEL_RESOLUTION);
    ledcSetup(c_i_PWMCH_WHEELRIGHT1, c_i_PWM_WHEEL_FREQ, c_i_PWM_WHEEL_RESOLUTION);
    ledcSetup(c_i_PWMCH_WHEELRIGHT2, c_i_PWM_WHEEL_FREQ, c_i_PWM_WHEEL_RESOLUTION);
    ledcSetup(c_i_PWMCH_LIFT1, c_i_PWM_LIFT_FREQ, c_i_PWM_LIFT_RESOLUTION);
    ledcSetup(c_i_PWMCH_LIFT2, c_i_PWM_LIFT_FREQ, c_i_PWM_LIFT_RESOLUTION);


    if (g_i_WheelDir_LeftFront >= 0) {
        ledcAttachPin(c_i_PIN_WHEEL_LEFTFRONT_PWM1, c_i_PWMCH_WHEELLEFT1);
        ledcAttachPin(c_i_PIN_WHEEL_LEFTFRONT_PWM2, c_i_PWMCH_WHEELLEFT2);
    }
    else {
        ledcAttachPin(c_i_PIN_WHEEL_LEFTFRONT_PWM2, c_i_PWMCH_WHEELLEFT1);
        ledcAttachPin(c_i_PIN_WHEEL_LEFTFRONT_PWM1, c_i_PWMCH_WHEELLEFT2);
    }
    if (g_i_WheelDir_LeftBack >= 0) {
        ledcAttachPin(c_i_PIN_WHEEL_LEFTBACK_PWM1, c_i_PWMCH_WHEELLEFT1);
        ledcAttachPin(c_i_PIN_WHEEL_LEFTBACK_PWM2, c_i_PWMCH_WHEELLEFT2);
    }
    else {
        ledcAttachPin(c_i_PIN_WHEEL_LEFTBACK_PWM2, c_i_PWMCH_WHEELLEFT1);
        ledcAttachPin(c_i_PIN_WHEEL_LEFTBACK_PWM1, c_i_PWMCH_WHEELLEFT2);
    }
    if (g_i_WheelDir_RightFront >= 0) {
        ledcAttachPin(c_i_PIN_WHEEL_RIGHTFRONT_PWM1, c_i_PWMCH_WHEELRIGHT1);
        ledcAttachPin(c_i_PIN_WHEEL_RIGHTFRONT_PWM2, c_i_PWMCH_WHEELRIGHT2);
    }
    else {
        ledcAttachPin(c_i_PIN_WHEEL_RIGHTFRONT_PWM2, c_i_PWMCH_WHEELRIGHT1);
        ledcAttachPin(c_i_PIN_WHEEL_RIGHTFRONT_PWM1, c_i_PWMCH_WHEELRIGHT2);
    }
    if (g_i_WheelDir_RightBack >= 0) {
        ledcAttachPin(c_i_PIN_WHEEL_RIGHTBACK_PWM1, c_i_PWMCH_WHEELRIGHT1);
        ledcAttachPin(c_i_PIN_WHEEL_RIGHTBACK_PWM2, c_i_PWMCH_WHEELRIGHT2);
    }
    else {
        ledcAttachPin(c_i_PIN_WHEEL_RIGHTBACK_PWM2, c_i_PWMCH_WHEELRIGHT1);
        ledcAttachPin(c_i_PIN_WHEEL_RIGHTBACK_PWM1, c_i_PWMCH_WHEELRIGHT2);
    }
    if (g_i_LiftDir >= 0) {
        ledcAttachPin(c_i_PIN_LIFT_PWM1, c_i_PWMCH_LIFT1);
        ledcAttachPin(c_i_PIN_LIFT_PWM2, c_i_PWMCH_LIFT2);
    }
    else {
        ledcAttachPin(c_i_PIN_LIFT_PWM2, c_i_PWMCH_LIFT1);
        ledcAttachPin(c_i_PIN_LIFT_PWM1, c_i_PWMCH_LIFT2);
    }

    MotorRun(0, 0);
    LiftRun(0);
}

void MotorRun(int mr_i_leftSpeed, int mr_i_rightSpeed) {
    if (mr_i_leftSpeed > 510) {
        mr_i_leftSpeed = 510;
    }
    else if (mr_i_leftSpeed < -510) {
        mr_i_leftSpeed = -510;
    }

    if (mr_i_rightSpeed > 510) {
        mr_i_rightSpeed = 510;
    }
    else if (mr_i_rightSpeed < -510) {
        mr_i_rightSpeed = -510;
    }

    if (mr_i_leftSpeed > 0) {
        ledcWrite(c_i_PWMCH_WHEELLEFT1, mr_i_leftSpeed);
        ledcWrite(c_i_PWMCH_WHEELLEFT2, 0);
    }
    else if (mr_i_leftSpeed == 0) {
        ledcWrite(c_i_PWMCH_WHEELLEFT1, 511);
        ledcWrite(c_i_PWMCH_WHEELLEFT2, 511);
    }
    else {
        ledcWrite(c_i_PWMCH_WHEELLEFT1, 0);
        ledcWrite(c_i_PWMCH_WHEELLEFT2, mr_i_leftSpeed * -1);
    }

    if (mr_i_rightSpeed > 0) {
        ledcWrite(c_i_PWMCH_WHEELRIGHT1, mr_i_rightSpeed);
        ledcWrite(c_i_PWMCH_WHEELRIGHT2, 0);
    }
    else if (mr_i_rightSpeed == 0) {
        ledcWrite(c_i_PWMCH_WHEELRIGHT1, 511);
        ledcWrite(c_i_PWMCH_WHEELRIGHT2, 511);
    }
    else {
        ledcWrite(c_i_PWMCH_WHEELRIGHT1, 0);
        ledcWrite(c_i_PWMCH_WHEELRIGHT2, mr_i_rightSpeed * -1);
    }
}

void LiftRun(int lr_i_speed) {
    if (lr_i_speed > 0) {
        ledcWrite(c_i_PWMCH_LIFT1, lr_i_speed);
        ledcWrite(c_i_PWMCH_LIFT2, 0);
    }
    else if (lr_i_speed == 0) {
        ledcWrite(c_i_PWMCH_LIFT1, 0);
        ledcWrite(c_i_PWMCH_LIFT2, 0);
    }
    else {
        ledcWrite(c_i_PWMCH_LIFT1, 0);
        ledcWrite(c_i_PWMCH_LIFT2, lr_i_speed * -1);
    }
}

void LiftToPositon(int ltp_i_pos) {
    if (ltp_i_pos >= 0 && ltp_i_pos <= 2) {
        if (g_i_LiftCurrentPosition < ltp_i_pos) {
            LiftRun(g_i_LiftSpeed);
        }
        else if (g_i_LiftCurrentPosition > ltp_i_pos) {
            LiftRun(g_i_LiftSpeed * -1);
        }
        
        if (g_i_LiftCurrentPosition == 0) {
            if (ltp_i_pos == 1) {
                delay(g_l_LiftMoveTime_Mid2Low);
            }
            if (ltp_i_pos == 2) {
                delay(g_l_LiftMoveTime_Mid2Low + g_l_LiftMoveTime_Mid2High);
            }
        }
        else if (g_i_LiftCurrentPosition == 1) {
            if (ltp_i_pos == 0) {
                delay(g_l_LiftMoveTime_Mid2Low);
            }
            if (ltp_i_pos == 2) {
                delay(g_l_LiftMoveTime_Mid2High);
            }
        }
        else if (g_i_LiftCurrentPosition == 2) {
            if (ltp_i_pos == 0) {
                delay(g_l_LiftMoveTime_Mid2Low + g_l_LiftMoveTime_Mid2High);
            }
            if (ltp_i_pos == 1) {
                delay(g_l_LiftMoveTime_Mid2High);
            }
        }
        
        g_i_LiftCurrentPosition = ltp_i_pos;
        
    }
    LiftRun(0);
}