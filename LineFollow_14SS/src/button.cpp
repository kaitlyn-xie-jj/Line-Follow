#include "button.h"

void InitButton() {
    for (int i = 0; i < 3; i++) {
        pinMode(c_i_PIN_BUTTONS[i], INPUT_PULLUP);
    }
}

bool GetButton(int eb_i_keyNum) {
    if (eb_i_keyNum < 1 || eb_i_keyNum > 3) {
        return false;
    }
    else {
        if (digitalRead(c_i_PIN_BUTTONS[eb_i_keyNum - 1]) == LOW) {
            return true;
        }
        else {
            return false;
        }
    }
}