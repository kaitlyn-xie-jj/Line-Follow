#include "greyscalesensor.h"
#include "motor.h"

static int g_i_SensorVal_Min[14], g_i_SensorVal_Max[14];

void InitGreyscale() {
	analogReadResolution(c_i_ANALOGREAD_RESOLUTION);

	EEPROM.begin(c_i_EEPROM_SIZE);
	for (int i = 0; i < 14; i++) {
		g_i_SensorVal_Min[i] = EEPROM.read(i);
		g_i_SensorVal_Max[i] = EEPROM.read(i + 14);
	}
}

int GetGreyscaleraw(int ggr_i_channle) {
	return analogRead(c_i_PIN_GREYSCALE[ggr_i_channle]);
}

int GetGreyscalevalue(int ggv_i_channle) {
	int value , values = 0;
	if (ggv_i_channle >= 0 && ggv_i_channle <= 13) {
    for (int i = 0; i < 2 ; i++) {
      value = GetGreyscaleraw(ggv_i_channle);
			if (value < g_i_SensorVal_Min[ggv_i_channle]) {
				value = g_i_SensorVal_Min[ggv_i_channle];
			}
			else if (value > g_i_SensorVal_Max[ggv_i_channle]) {
				value = g_i_SensorVal_Max[ggv_i_channle];
			}
			value = map(value, g_i_SensorVal_Min[ggv_i_channle], g_i_SensorVal_Max[ggv_i_channle], 0, 30);
      values = values + value;
    }
	}
	else {
		return -1;
	}
	return values / 2;
}

void GreycaleCalibration() {
	int sc_i_sensorVal_Min[14], sc_i_sensorVal_Max[14];
	unsigned long sc_i_timer;

	for (int i = 0; i < 14; i++) {
		sc_i_sensorVal_Min[i] = 65;
		sc_i_sensorVal_Max[i] = -1;
	}

	MotorRun(c_i_SENSORCAL_GOSPD, c_i_SENSORCAL_GOSPD * -1);
	sc_i_timer = millis();
	while (millis() - sc_i_timer < c_i_SENSORCAL_GOTIME) {
		for (int i = 0; i < 14; i++) {
			int value = GetGreyscaleraw(i);
			if (value < sc_i_sensorVal_Min[i]) {
				sc_i_sensorVal_Min[i] = value;
			}
			else if (value > sc_i_sensorVal_Max[i]) {
				sc_i_sensorVal_Max[i] = value;
			}
		 }
	}
	MotorRun(0, 0);
//8-57
	for (int i = 0; i < 14; i++) {
		g_i_SensorVal_Min[i] = sc_i_sensorVal_Min[i] + (sc_i_sensorVal_Max[i] - sc_i_sensorVal_Min[i]) / 4;
		g_i_SensorVal_Max[i] = sc_i_sensorVal_Max[i] - (sc_i_sensorVal_Max[i] - sc_i_sensorVal_Min[i]) / 10;
		EEPROM.write(i, g_i_SensorVal_Min[i]);
		EEPROM.write(i + 14, g_i_SensorVal_Max[i]);
		EEPROM.commit();
	}
}