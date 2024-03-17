#include "facefuture.h"
int lrValue = 0;
static int c_i_LINEFOLLOW_KP = 0;
static int c_i_LINEFOLLOW_KD = 0;
static int g_i_LinePos_Last = 0;
static int g_i_LineOutDir = 0;

static int start = 0;
float weights[14] = {-210,-180, -140, -100, -60, -30, -10, 10, 30, 60, 100, 140, 180, 210};
static int g_i_GreyScaleValues[14];

/*void smoothSensorReadings(int* readings, int numReadings) {
    for (int i = 1; i < numReadings - 1; i++) {
        readings[i] = (readings[i-1] + readings[i] + readings[i+1]) / 3;
    }
}*/
void SetLinefollow_PD(int slf_i_kp, int slf_i_kd) {
	c_i_LINEFOLLOW_KP = slf_i_kp;
	c_i_LINEFOLLOW_KD = slf_i_kd;
}

void WSR_GetGreyscaleValues() {
	for (int i = 0; i < 14; i++) {
		g_i_GreyScaleValues[i] = GetGreyscalevalue(i);
	}
	if(g_i_GreyScaleValues[0] > 25){lrValue = -1;}
	else if(g_i_GreyScaleValues[13] > 25){lrValue = 1;}
	else{lrValue = 0;}
}
int WSR_GetLinePosiotion() {     //加权平均数
    static int lastpos = 0;
    int glp_i_linepos = 0;
    int glp_i_div = 0;

    WSR_GetGreyscaleValues();
    //smoothSensorReadings(g_i_GreyScaleValues, 14); // 平滑传感器读数

    for (int j = 0; j < 14; j++) {
        glp_i_linepos += g_i_GreyScaleValues[j] * weights[j];
        glp_i_div += g_i_GreyScaleValues[j];
    }

    if (glp_i_div != 0) {
        lastpos = glp_i_linepos / glp_i_div;
        return lastpos;
    } else {
		if(lrValue == -1){lastpos = -210;}
		if(lrValue == 1){lastpos = 210;}

        return lastpos; // 如果没有检测到线，则返回上一次的位置
    }
}

void LineFollow(int lf_i_speed) {
	long lf_l_linepos = 0;
	int lf_i_leftSpeed = 0, lf_i_rightSpeed = 0;

	lf_l_linepos = WSR_GetLinePosiotion();
	lf_i_leftSpeed = lf_i_speed + lf_l_linepos * c_i_LINEFOLLOW_KP / 100;
	lf_i_rightSpeed = lf_i_speed - lf_l_linepos * c_i_LINEFOLLOW_KP / 100;
	lf_i_leftSpeed = lf_i_leftSpeed + (lf_l_linepos - g_i_LinePos_Last) * c_i_LINEFOLLOW_KD / 100;
	lf_i_rightSpeed = lf_i_rightSpeed - (lf_l_linepos - g_i_LinePos_Last) * c_i_LINEFOLLOW_KD / 100;
	MotorRun(lf_i_leftSpeed, lf_i_rightSpeed);

	g_i_LinePos_Last = lf_l_linepos;
}
void LineDelay(int speed,int t)
{
    start = millis();
    while (millis() - start < t)
    {
    LineFollow(speed);
    }
}

/*
int WSR_GetLinePosiotion() {
	int glp_i_linepos, glp_i_div, glp_i_onine, glp_i_linepos_sum = 0;
	int glp_i_leftcheck = 0, glp_i_rightcheck = 0;
		glp_i_linepos = 0;
		glp_i_div = 0;
		glp_i_onine = 0;
		WSR_GetGreyscaleValues();
		for (int j = 0; j < 13; j++) {
			int ratio;
			ratio = (j - 6) * 30;
			glp_i_linepos = glp_i_linepos + g_i_GreyScaleValues[j] * ratio;
			glp_i_div = glp_i_div + g_i_GreyScaleValues[j];
			if (g_i_GreyScaleValues[j] > 10) {
				glp_i_onine = 1;
				if (j == 0) {
					glp_i_leftcheck++;
				}
				else if (j == 6) {
					glp_i_rightcheck++;
				}
			}
		}
		if (glp_i_onine == 1) {
			glp_i_linepos = glp_i_linepos / glp_i_div;
		}
		else {
			if (g_i_LineOutDir > 0) {
				glp_i_linepos = 182;
			}
			else {
				glp_i_linepos = -182;
			}
		}
		glp_i_linepos_sum = glp_i_linepos_sum + glp_i_linepos;
	


	if (glp_i_leftcheck > glp_i_rightcheck) {
		g_i_LineOutDir = -1;
	}
	else if (glp_i_leftcheck < glp_i_rightcheck) {
		g_i_LineOutDir = 1;
	}

	return glp_i_linepos_sum;
}
*/
