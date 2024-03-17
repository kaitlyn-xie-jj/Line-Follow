#include "src/motor.h"
#include "src/button.h"
#include "src/greyscalesensor.h"


void SetLinefollow_PD(int slf_i_kp, int slf_i_kd);
void WSR_GetGreyscaleValues();
int WSR_GetLinePosiotion();
void LineFollow(int lf_i_speed);
void LineDelay(int speed, int t);
